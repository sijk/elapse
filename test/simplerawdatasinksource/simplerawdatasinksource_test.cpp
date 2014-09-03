#include <gtest/gtest.h>
#include <QApplication>
#include <QLineEdit>
#include <QSignalSpy>
#include "../test_utils.h"
#include "simplerawdatasink.h"
#include "simplerawdatasource.h"

using elapse::data::Signal;


class SimpleRawDataSinkNoGui : public elapse::coreplugin::SimpleRawDataSink
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

    SimpleRawDataSinkNoGui dataSink;
    QString dataDir;
};


TEST_F(SimpleRawDataSinkTest, InitiallyNeedsNewCaptureInfo)
{
    EXPECT_TRUE(dataSink.needsNewCaptureInfo());
}

TEST_F(SimpleRawDataSinkTest, DoesntNeedNewCaptureInfoAfterGetTmp)
{
    EXPECT_TRUE(dataSink.needsNewCaptureInfo());
    EXPECT_TRUE(dataSink.getCaptureInfo());
    EXPECT_FALSE(dataSink.needsNewCaptureInfo());
}

TEST_F(SimpleRawDataSinkTest, OnlyNeedsNewCaptureInfoOnce)
{
    EXPECT_TRUE(dataSink.needsNewCaptureInfo());
    EXPECT_TRUE(dataSink.getCaptureInfo());
    EXPECT_FALSE(dataSink.needsNewCaptureInfo());
    EXPECT_TRUE(dataSink.start());
    dataSink.stop();
    EXPECT_FALSE(dataSink.needsNewCaptureInfo());
}

TEST_F(SimpleRawDataSinkTest, SavesConfig)
{
    const QMap<QString, QVariantMap> srcConfig = {
        {"test", {{"prop1", 42},{"prop2",true}}}
    };

    EXPECT_TRUE(dataSink.getCaptureInfo());
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
    EXPECT_TRUE(dataSink.getCaptureInfo());
    ASSERT_TRUE(dataSink.start());
    dataSink.saveData(Signal::EEG, "EEG DATA");
    dataSink.saveData(Signal::IMU, "IMU DATA");
    dataSink.saveData(Signal::EEG, "EEG DATA");
    dataSink.stop();

    QFileInfoList files = QDir(dataDir, "*.dat").entryInfoList();
    ASSERT_EQ(files.count(), 1);
    QFile file(files.first().absoluteFilePath());
    ASSERT_TRUE(file.open(QFile::ReadOnly));
    QDataStream stream(&file);

    int dt;
    Signal::Type signalType;
    QByteArray data;
    auto expectNextDataToBe = [&](Signal::Type t, const QByteArray &d) {
        stream >> dt >> (int&)signalType >> data;
        EXPECT_GE(dt, 0);
        EXPECT_EQ(signalType, t);
        EXPECT_EQ(data, d);
    };
    expectNextDataToBe(Signal::EEG, "EEG DATA");
    expectNextDataToBe(Signal::IMU, "IMU DATA");
    expectNextDataToBe(Signal::EEG, "EEG DATA");
    EXPECT_TRUE(stream.atEnd());
}

TEST_F(SimpleRawDataSinkTest, SinkAndSource)
{
    const QMap<QString, QVariantMap> config = {
        {"test", {{"prop1", 42},{"prop2",true}}}
    };

    EXPECT_TRUE(dataSink.getCaptureInfo());
    ASSERT_TRUE(dataSink.start());
    dataSink.saveDeviceConfig(config);
    dataSink.saveData(Signal::EEG, "EEG DATA");
    dataSink.saveData(Signal::IMU, "IMU DATA");
    dataSink.saveData(Signal::EEG, "EEG DATA");
    dataSink.stop();

    QFileInfoList files = QDir(dataDir, "*.dat").entryInfoList();
    ASSERT_EQ(files.count(), 1);
    QString filePath = files.first().absoluteFilePath();

    elapse::coreplugin::SimpleRawDataSource src;
    QSignalSpy eegReady(&src, SIGNAL(eegReady(QByteArray)));
    QSignalSpy imuReady(&src, SIGNAL(imuReady(QByteArray)));
    QSignalSpy videoReady(&src, SIGNAL(videoReady(QByteArray)));
    QSignalSpy finished(&src, SIGNAL(finished()));

    auto widget = src.getWidget();
    auto lineEdit = widget->findChild<QLineEdit*>();
    lineEdit->setText(filePath);
    src.start();

    EXPECT_EQ(src.get("test", "prop1").toInt(), 42);
    EXPECT_EQ(src.get("test", "prop2").toBool(), true);
    EXPECT_FALSE(src.get("test", "prop3").isValid());

    finished.wait(500);
    ASSERT_EQ(finished.count(), 1);
    src.stop();

    EXPECT_EQ(eegReady.count(), 2);
    EXPECT_EQ(imuReady.count(), 1);
    EXPECT_EQ(videoReady.count(), 0);

    EXPECT_EQ(eegReady.at(0).first(), "EEG DATA");
    EXPECT_EQ(imuReady.at(0).first(), "IMU DATA");
    EXPECT_EQ(eegReady.at(1).first(), "EEG DATA");
}

