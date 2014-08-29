#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QSignalSpy>
#include "../test_utils.h"

#include <QVariant>
#include "elapse/elements/datasource.h"
#include "deviceproxy.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::Contains;


class MockOfflineDataSource : public elapse::OfflineDataSource
{
public:
    MockOfflineDataSource()
    {
        EXPECT_CALL(*this, get(QString("eeg"),QString("nChannels")))
                .WillRepeatedly(Return(QVariant::fromValue(8)));
        exposeDeviceInterface();
    }

    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD2(get, QVariant(const QString &, const QString &));
};


TEST(ConfigDBusTest, GetConfigDirectly)
{
    MockOfflineDataSource src;
    EXPECT_CALL(src, get(QString("imu"),QString("sampleRate")))
            .WillOnce(Return(QVariant::fromValue(42)));

    EXPECT_EQ(src.get("imu", "sampleRate").toInt(), 42);
}

TEST(ConfigDBusTest, GetConfigViaDBus)
{
    MockOfflineDataSource src;
    EXPECT_CALL(src, get(QString("imu"),QString("sampleRate")))
            .WillOnce(Return(QVariant::fromValue(42)));
    EXPECT_CALL(src, get(QString("eeg/channel/0"),QString("gain")))
            .WillOnce(Return(QVariant::fromValue(42)));

    DeviceProxy proxy;
    QSignalSpy connected(&proxy, SIGNAL(connected()));
    QSignalSpy error(&proxy, SIGNAL(error(QString)));

    proxy.connectTo("localhost");
    connected.wait(500);
    ASSERT_EQ(connected.count(), 1);

    ASSERT_TRUE(proxy.device()->isAccessible());
    EXPECT_EQ(proxy.device()->imu()->sampleRate(), 42u);
    EXPECT_EQ(proxy.device()->eeg()->channel(0)->gain(), 42);

    EXPECT_EQ(error.count(), 0);
}

TEST(ConfigDBusTest, GetDeviceConfig)
{
    MockOfflineDataSource src;
    EXPECT_CALL(src, get(_,_))
            .WillRepeatedly(Return(QVariant::fromValue(42)));
    EXPECT_CALL(src, get(QString("eeg"),QString("nChannels")))
            .WillRepeatedly(Return(QVariant::fromValue(2)));

    DeviceProxy proxy;
    QSignalSpy connected(&proxy, SIGNAL(connected()));
    QSignalSpy error(&proxy, SIGNAL(error(QString)));

    proxy.connectTo("localhost");
    connected.wait(500);
    ASSERT_EQ(connected.count(), 1);

    ASSERT_TRUE(proxy.device()->isAccessible());
    auto cfg = proxy.getDeviceConfig();
    auto subSystems = cfg.keys();
    EXPECT_THAT(subSystems, Contains("battery"));
    EXPECT_THAT(subSystems, Contains("imu"));
    EXPECT_THAT(subSystems, Contains("camera"));
    EXPECT_THAT(subSystems, Contains("eeg"));
    EXPECT_THAT(subSystems, Contains("eeg/channel/0"));
    EXPECT_THAT(subSystems, Contains("eeg/channel/1"));
    EXPECT_THAT(cfg.value("battery").keys(), Contains("voltage"));
    EXPECT_EQ(cfg.value("eeg").value("nChannels").toInt(), 2);

    EXPECT_EQ(error.count(), 0);
}

TEST(ConfigDBusTest, DetectDisconnection)
{
    auto src = new MockOfflineDataSource;

    DeviceProxy proxy;
    QSignalSpy connected(&proxy, SIGNAL(connected()));

    proxy.connectTo("localhost");
    connected.wait(500);
    ASSERT_EQ(connected.count(), 1);

    ASSERT_TRUE(proxy.device()->isAccessible());
    delete src;
    ASSERT_FALSE(proxy.device()->isAccessible());
}

