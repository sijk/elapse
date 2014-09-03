#include <gtest/gtest.h>
#include <QCoreApplication>
#include "../test_utils.h"
#include "pluginmanager.h"
#include "pluginmanager_p.h"

using elapse::elements::FeatureExtractor;
namespace plugin = elapse::plugin;


class PythonBindingsTest : public testing::Test
{
public:
    void SetUp()
    {
        manager = new plugin::Manager;
        priv = plugin::ManagerPrivate::expose(manager);
        priv->hosts.remove(plugin::HostID::Static);
        manager->setSearchPath(qApp->applicationDirPath() + "/plugins");
    }

    void TearDown()
    {
        delete manager;
    }

    plugin::Manager *manager;
    plugin::ManagerPrivate *priv;
};


TEST_F(PythonBindingsTest, RunPythonTests)
{
    ASSERT_EQ(priv->pluginData.size(), 1);
    const plugin::PluginData &info = priv->pluginData.first();
    plugin::Host *host = priv->hosts[info.plugin.host];

    for (const plugin::ClassInfo &test : info.classes) {
        auto pyTestPassed = host->instantiate<FeatureExtractor>(info.plugin, test);
        if (!pyTestPassed)
            ADD_FAILURE_AT(test.className.mid(5).toLatin1().constData(), 0);
    }
}
