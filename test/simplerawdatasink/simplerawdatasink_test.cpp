#include <gtest/gtest.h>
#include <QApplication>
#include "../test_utils.h"
#include "simplerawdatasinkdelegate.h"


class SimpleRawDataSinkDelegateNoGui : public SimpleRawDataSinkDelegate
{
protected:
    QString getDirectory() const
    {
        return QDir(qApp->applicationDirPath()).absoluteFilePath("tmp");
    }
};


class SimpleRawDataSinkTest : public testing::Test
{
public:
    void SetUp()
    {
        dataDir = QDir(qApp->applicationDirPath()).absoluteFilePath("tmp");
        ASSERT_FALSE(QDir(dataDir).exists());
        ASSERT_TRUE(QDir().mkpath(dataDir));
    }

    void TearDown()
    {
        ASSERT_TRUE(recursiveRmDir(dataDir));
    }

    SimpleRawDataSinkDelegateNoGui dataSink;
    QString dataDir;
};


TEST_F(SimpleRawDataSinkTest, InitiallyNeedsNewSessionData)
{
    EXPECT_TRUE(dataSink.needsNewSessionData());
}

TEST_F(SimpleRawDataSinkTest, DoesntNeedNewSessionDataAfterGetTmp)
{
    EXPECT_TRUE(dataSink.needsNewSessionData());
    EXPECT_TRUE(dataSink.getSessionData());
    EXPECT_FALSE(dataSink.needsNewSessionData());
}

TEST_F(SimpleRawDataSinkTest, OnlyNeedsNewSessionDataOnce)
{
    EXPECT_TRUE(dataSink.needsNewSessionData());
    EXPECT_TRUE(dataSink.getSessionData());
    EXPECT_FALSE(dataSink.needsNewSessionData());
    EXPECT_TRUE(dataSink.start());
    dataSink.stop();
    EXPECT_FALSE(dataSink.needsNewSessionData());
}

TEST_F(SimpleRawDataSinkTest, SavesConfig)
{
    const QMap<QString, QVariantMap> srcConfig = {
        {"test", {{"prop1", 42},{"prop2",true}}}
    };

    EXPECT_TRUE(dataSink.getSessionData());
    ASSERT_TRUE(dataSink.start());
    dataSink.saveDeviceConfig(srcConfig);
    dataSink.stop();

    QFileInfoList files = QDir(dataDir, "*.dat").entryInfoList();
    ASSERT_EQ(files.count(), 1);
    QFile file(files.first().absoluteFilePath());
    ASSERT_TRUE(file.open(QFile::ReadOnly));
    QDataStream stream(&file);

    QMap<QString, QVariantMap> destConfig;
    stream >> destConfig;
    EXPECT_TRUE(srcConfig == destConfig);
    EXPECT_TRUE(stream.atEnd());
}

TEST_F(SimpleRawDataSinkTest, SavesData)
{
    EXPECT_TRUE(dataSink.getSessionData());
    ASSERT_TRUE(dataSink.start());
    dataSink.saveData(elapse::Signal::EEG, "EEG DATA");
    dataSink.saveData(elapse::Signal::IMU, "IMU DATA");
    dataSink.saveData(elapse::Signal::EEG, "EEG DATA");
    dataSink.stop();

    QFileInfoList files = QDir(dataDir, "*.dat").entryInfoList();
    ASSERT_EQ(files.count(), 1);
    QFile file(files.first().absoluteFilePath());
    ASSERT_TRUE(file.open(QFile::ReadOnly));
    QDataStream stream(&file);

    elapse::Signal::Type signalType;
    QByteArray data;
    auto expectNextDataToBe = [&](elapse::Signal::Type t, const QByteArray &d) {
        stream >> (int&)signalType >> data;
        EXPECT_EQ(signalType, t);
        EXPECT_EQ(data, d);
    };
    expectNextDataToBe(elapse::Signal::EEG, "EEG DATA");
    expectNextDataToBe(elapse::Signal::IMU, "IMU DATA");
    expectNextDataToBe(elapse::Signal::EEG, "EEG DATA");
    EXPECT_TRUE(stream.atEnd());
}


