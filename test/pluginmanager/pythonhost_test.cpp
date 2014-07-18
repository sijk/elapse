#include <gtest/gtest.h>
#include <QCoreApplication>

#include "pythonpluginhost.h"

class PythonPluginHostTest : public ::testing::Test
{
public:
    void SetUp()
    {
        QDir pluginDir(qApp->applicationDirPath());
        pluginDir.cdUp();
        pluginDir.cd("test_plugins");

        bazPluginPath = pluginDir.absoluteFilePath("bazplugin");
    }

    PythonPluginHost host;
    QString bazPluginPath;
};


TEST_F(PythonPluginHostTest, InfoForBazPlugin)
{
    auto info = host.getInfo(bazPluginPath);

    EXPECT_EQ(info.plugin.host, PYTHON);
    EXPECT_EQ(info.plugin.name, QString("bazplugin"));
    EXPECT_EQ(info.plugin.path, bazPluginPath);

    EXPECT_EQ(info.classes.size(), 2);

    EXPECT_EQ(info.classes[0].className, QString("BazEegFeatEx"));
    EXPECT_EQ(info.classes[0].elementClass, QString("FeatureExtractor"));
    EXPECT_EQ(info.classes[0].signalType, elapse::Signal::EEG);

    EXPECT_EQ(info.classes[1].className, QString("BazImuFeatEx"));
    EXPECT_EQ(info.classes[1].elementClass, QString("FeatureExtractor"));
    EXPECT_EQ(info.classes[1].signalType, elapse::Signal::IMU);
}

TEST_F(PythonPluginHostTest, InstantiateBazEegFeatEx)
{
    auto info = host.getInfo(bazPluginPath);
    auto cls = info.classes[0];
    auto instance = host.instantiateClass(info.plugin, cls);
    ASSERT_FALSE(instance.isNull());
    EXPECT_STREQ(instance->metaObject()->superClass()->className(),
                 "elapse::FeatureExtractor");
}
