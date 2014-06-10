#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QStandardItemModel>
#include "../test_utils.h"

#include "pluginmanager.h"
#include "pluginmanager_p.h"

class PluginManagerTest : public testing::Test
{
public:
    void SetUp()
    {
        manager = new PluginManager;
        manager->setSearchPath(qApp->applicationDirPath() + "/../test_plugins");

        priv = PluginManagerPrivate::expose(manager);
    }

    void TearDown()
    {
        delete manager;
    }

    PluginManager *manager;
    PluginManagerPrivate *priv;

    SuppressLogging nolog;
};


TEST_F(PluginManagerTest, SetSearchPath)
{
    QDir newPath("/tmp");
    manager->setSearchPath(newPath);
    EXPECT_EQ(manager->searchPath(), newPath);
}
