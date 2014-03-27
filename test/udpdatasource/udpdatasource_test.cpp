#include <gtest/gtest.h>
#include <QtTest/QSignalSpy>
#include <QUdpSocket>
#include "udpdatasource.h"

#define EEG_PORT    5000
#define IMU_PORT    6000
#define VIDEO_PORT  7000


class UdpDataSourceTest : public testing::Test
{
public:
    UdpDataSourceTest() :
        eegReady(&src, SIGNAL(eegReady(QByteArray))),
        videoReady(&src, SIGNAL(videoReady(QByteArray))),
        imuReady(&src, SIGNAL(imuReady(QByteArray))),
        started(&src, SIGNAL(started())),
        error(&src, SIGNAL(error(QString))),
        testData("TEST")
    { }

    void sendTestDataToPort(quint16 port)
    {
        QUdpSocket().writeDatagram(testData, QHostAddress::LocalHost, port);
    }

    UdpDataSource src;
    QSignalSpy eegReady;
    QSignalSpy videoReady;
    QSignalSpy imuReady;
    QSignalSpy started;
    QSignalSpy error;
    QByteArray testData;
};


TEST_F(UdpDataSourceTest, Signals)
{
    src.start();

    sendTestDataToPort(EEG_PORT);
    eegReady.wait(500);
    EXPECT_EQ(eegReady.count(), 1);
    EXPECT_EQ(imuReady.count(), 0);
    EXPECT_EQ(videoReady.count(), 0);
    EXPECT_EQ(eegReady.first().first(), testData);
    EXPECT_EQ(started.count(), 0);
    EXPECT_EQ(error.count(), 0);

    sendTestDataToPort(IMU_PORT);
    imuReady.wait(500);
    EXPECT_EQ(eegReady.count(), 1);
    EXPECT_EQ(imuReady.count(), 1);
    EXPECT_EQ(videoReady.count(), 0);
    EXPECT_EQ(imuReady.first().first(), testData);
    EXPECT_EQ(started.count(), 0);
    EXPECT_EQ(error.count(), 0);

    sendTestDataToPort(VIDEO_PORT);
    videoReady.wait(500);
    EXPECT_EQ(eegReady.count(), 1);
    EXPECT_EQ(imuReady.count(), 1);
    EXPECT_EQ(videoReady.count(), 1);
    EXPECT_EQ(videoReady.first().first(), testData);
    EXPECT_EQ(started.count(), 1);
    EXPECT_EQ(error.count(), 0);

    src.stop();
}

TEST_F(UdpDataSourceTest, NoSignalsBeforeStart)
{
    sendTestDataToPort(EEG_PORT);
    eegReady.wait(500);
    EXPECT_EQ(eegReady.count(), 0);
    EXPECT_EQ(imuReady.count(), 0);
    EXPECT_EQ(videoReady.count(), 0);
    EXPECT_EQ(started.count(), 0);
    EXPECT_EQ(error.count(), 0);
}

TEST_F(UdpDataSourceTest, NoSignalsAfterStopped)
{
    src.start();
    src.stop();

    sendTestDataToPort(EEG_PORT);
    eegReady.wait(500);
    EXPECT_EQ(eegReady.count(), 0);
    EXPECT_EQ(imuReady.count(), 0);
    EXPECT_EQ(videoReady.count(), 0);
    EXPECT_EQ(started.count(), 0);
    EXPECT_EQ(error.count(), 0);
}

