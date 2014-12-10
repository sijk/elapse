#include <gtest/gtest.h>
#include <QCoreApplication>
#include <elapse/elements/decoder.h>

#include "nativepluginhost.h"

using elapse::elements::SampleDecoder;
using elapse::data::Signal;
namespace plugin = elapse::plugin;


class PublicNativePluginHost : public plugin::NativeHost
{
    // Make methods public for testability
public:
    using plugin::NativeHost::getInfo;
};


class NativePluginHostTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        QDir pluginDir(qApp->applicationDirPath());
        pluginDir.cdUp();
        pluginDir.cd("test_plugins");

        fooPluginPath = pluginDir.absoluteFilePath("libfooplugin.so");
        barPluginPath = pluginDir.absoluteFilePath("libbarplugin.so");
    }

    PublicNativePluginHost host;
    QString fooPluginPath;
    QString barPluginPath;
};


TEST_F(NativePluginHostTest, InfoForFooPlugin)
{
    auto info = host.getInfo(fooPluginPath);

    EXPECT_EQ(info.plugin.host, plugin::HostID::Native);
    EXPECT_EQ(info.plugin.name, QString("FooPlugin"));
    EXPECT_EQ(info.plugin.path, fooPluginPath);

    EXPECT_EQ(info.classes.size(), 2);

    EXPECT_EQ(info.classes[0].className, QString("FooEegDecoder"));
    EXPECT_EQ(info.classes[0].elementClass, QString("SampleDecoder"));
    EXPECT_EQ(info.classes[0].signalType, Signal::EEG);

    EXPECT_EQ(info.classes[1].className, QString("FooDummySource"));
    EXPECT_EQ(info.classes[1].elementClass, QString("DataSource"));
    EXPECT_EQ(info.classes[1].signalType, Signal::INVALID);
}

TEST_F(NativePluginHostTest, InfoForBarPlugin)
{
    auto info = host.getInfo(barPluginPath);

    EXPECT_EQ(info.plugin.host, plugin::HostID::Native);
    EXPECT_EQ(info.plugin.name, QString("BarPlugin"));
    EXPECT_EQ(info.plugin.path, barPluginPath);

    EXPECT_EQ(info.classes.size(), 2);

    EXPECT_EQ(info.classes[0].className, QString("BarEegDecoder"));
    EXPECT_EQ(info.classes[0].elementClass, QString("SampleDecoder"));
    EXPECT_EQ(info.classes[0].signalType, Signal::EEG);

    EXPECT_EQ(info.classes[1].className, QString("BarVideoDecoder"));
    EXPECT_EQ(info.classes[1].elementClass, QString("SampleDecoder"));
    EXPECT_EQ(info.classes[1].signalType, Signal::VIDEO);
}

TEST_F(NativePluginHostTest, InstantiateFooEegDecoder)
{
    auto info = host.getInfo(fooPluginPath);
    auto cls = info.classes[0];
    auto instance = host.instantiate<SampleDecoder>(info.plugin, cls);
    ASSERT_FALSE(!instance);
    EXPECT_EQ(instance->metaObject()->className(), cls.className);
}
