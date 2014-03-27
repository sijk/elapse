#include <gtest/gtest.h>
#include <QApplication>
#include "../test_utils.h"
#include "simplerawdatasinkdelegate.h"


class SimpleRawDataSinkDelegateNoGui : public SimpleRawDataSinkDelegate
{
public:
    SimpleRawDataSinkDelegateNoGui() : SimpleRawDataSinkDelegate() {}

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

