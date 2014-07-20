#include <gtest/gtest.h>
#include <QCoreApplication>

#include "nativepluginhost.h"

class NativePluginHostTest : public ::testing::Test
{
public:
    void SetUp()
    {
        QDir pluginDir(qApp->applicationDirPath());
        pluginDir.cdUp();
        pluginDir.cd("test_plugins");

        fooPluginPath = pluginDir.absoluteFilePath("libfooplugin.so");
        barPluginPath = pluginDir.absoluteFilePath("libbarplugin.so");
    }

    NativePluginHost host;
    QString fooPluginPath;
    QString barPluginPath;
};


TEST_F(NativePluginHostTest, InfoForFooPlugin)
{
    auto info = host.getInfo(fooPluginPath);

    EXPECT_EQ(info.plugin.host, PluginHostID::Native);
    EXPECT_EQ(info.plugin.name, QString("FooPlugin"));
    EXPECT_EQ(info.plugin.path, fooPluginPath);

    EXPECT_EQ(info.classes.size(), 2);

    EXPECT_EQ(info.classes[0].className, QString("FooEegDecoder"));
    EXPECT_EQ(info.classes[0].elementClass, QString("SampleDecoder"));
    EXPECT_EQ(info.classes[0].signalType, elapse::Signal::EEG);

    EXPECT_EQ(info.classes[1].className, QString("FooDummySource"));
    EXPECT_EQ(info.classes[1].elementClass, QString("DataSource"));
    EXPECT_EQ(info.classes[1].signalType, elapse::Signal::INVALID);
}

TEST_F(NativePluginHostTest, InfoForBarPlugin)
{
    auto info = host.getInfo(barPluginPath);

    EXPECT_EQ(info.plugin.host, PluginHostID::Native);
    EXPECT_EQ(info.plugin.name, QString("BarPlugin"));
    EXPECT_EQ(info.plugin.path, barPluginPath);

    EXPECT_EQ(info.classes.size(), 2);

    EXPECT_EQ(info.classes[0].className, QString("BarEegDecoder"));
    EXPECT_EQ(info.classes[0].elementClass, QString("SampleDecoder"));
    EXPECT_EQ(info.classes[0].signalType, elapse::Signal::EEG);

    EXPECT_EQ(info.classes[1].className, QString("BarVideoDecoder"));
    EXPECT_EQ(info.classes[1].elementClass, QString("SampleDecoder"));
    EXPECT_EQ(info.classes[1].signalType, elapse::Signal::VIDEO);
}

TEST_F(NativePluginHostTest, InstantiateFooEegDecoder)
{
    auto info = host.getInfo(fooPluginPath);
    auto cls = info.classes[0];
    auto instance = host.instantiateClass(info.plugin, cls);
    ASSERT_FALSE(instance.isNull());
    EXPECT_EQ(instance->metaObject()->className(), cls.className);
}
