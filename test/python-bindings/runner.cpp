#include <gtest/gtest.h>
#include <QCoreApplication>
#include "../test_utils.h"
#include "pluginmanager.h"
#include "pluginmanager_p.h"


class PythonBindingsTest : public testing::Test
{
public:
    void SetUp()
    {
        manager = new PluginManager;
        priv = PluginManagerPrivate::expose(manager);
        priv->hosts.remove(PluginHostID::Static);
        manager->setSearchPath(qApp->applicationDirPath() + "/plugins");
    }

    void TearDown()
    {
        delete manager;
    }

    PluginManager *manager;
    PluginManagerPrivate *priv;

    SuppressLogging nolog;
};


TEST_F(PythonBindingsTest, RunPythonTests)
{
    ASSERT_EQ(priv->pluginData.size(), 1);
    const PluginData &info = priv->pluginData.first();
    PluginHost *host = priv->hosts[info.plugin.host];

    for (const ClassInfo &test : info.classes) {
        auto passed = host->instantiate<elapse::FeatureExtractor>(info.plugin, test);
        EXPECT_TRUE(passed)
                << "Python test '" << test.className.mid(5).toStdString()
                << "' failed.";
        passed.clear();
    }
}
