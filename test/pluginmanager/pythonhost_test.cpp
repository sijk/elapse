#include <gtest/gtest.h>
#include <QCoreApplication>
#include <elapse/elements/featurextractor.h>

#include "pythonpluginhost.h"

using elapse::elements::FeatureExtractor;


// Make methods public for testability
class PublicPythonPluginHost : public elapse::plugin::PythonHost
{
public:
    using elapse::plugin::PythonHost::getInfo;
};

class PythonPluginHostTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        QDir pluginDir(qApp->applicationDirPath());
        pluginDir.cdUp();
        pluginDir.cd("test_plugins");

        bazPluginPath = pluginDir.absoluteFilePath("bazplugin");
    }

    PublicPythonPluginHost host;
    QString bazPluginPath;
};

TEST_F(PythonPluginHostTest, NoInfoForNonExistentPlugin)
{
    auto info = host.getInfo("/not/a/real/plugin");

    EXPECT_EQ(info.plugin.name, QString());
    EXPECT_EQ(info.plugin.path, QString());
    EXPECT_EQ(info.classes.size(), 0);
}

TEST_F(PythonPluginHostTest, InfoForBazPlugin)
{
    auto info = host.getInfo(bazPluginPath);

    EXPECT_EQ(info.plugin.host, elapse::plugin::HostID::Python);
    EXPECT_EQ(info.plugin.name, QString("bazplugin"));
    EXPECT_EQ(info.plugin.path, bazPluginPath);

    EXPECT_EQ(info.classes.size(), 2);

    EXPECT_EQ(info.classes[0].className, QString("BazEegFeatEx"));
    EXPECT_EQ(info.classes[0].elementClass, QString("FeatureExtractor"));
    EXPECT_EQ(info.classes[0].signalType, elapse::data::Signal::EEG);

    EXPECT_EQ(info.classes[1].className, QString("BazImuFeatEx"));
    EXPECT_EQ(info.classes[1].elementClass, QString("FeatureExtractor"));
    EXPECT_EQ(info.classes[1].signalType, elapse::data::Signal::IMU);
}

TEST_F(PythonPluginHostTest, InstantiateBazEegFeatEx)
{
    auto info = host.getInfo(bazPluginPath);
    auto cls = info.classes[0];
    auto instance = host.instantiate<FeatureExtractor>(info.plugin, cls);
    ASSERT_FALSE(!instance);
    EXPECT_EQ(instance->metaObject()->superClass(),
              &FeatureExtractor::staticMetaObject);
}
