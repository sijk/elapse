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
        priv = PluginManagerPrivate::expose(manager);
        priv->hosts.remove(PluginHostID::Static);
        testPluginPath = qApp->applicationDirPath() + "/../test_plugins";
        qxtLog->enableAllLogLevels();
    }

    void TearDown()
    {
        delete manager;
    }

    PluginManager *manager;
    PluginManagerPrivate *priv;
    QString testPluginPath;

    SuppressLogging nolog;
};


TEST_F(PluginManagerTest, SetSearchPath)
{
    QDir newPath("/tmp");
    manager->setSearchPath(newPath);
    EXPECT_EQ(manager->searchPath().absolutePath(), newPath.absolutePath());
}

TEST_F(PluginManagerTest, SearchForPlugins)
{
    manager->setSearchPath(testPluginPath);

    EXPECT_EQ(priv->pluginData.size(), 3);
    EXPECT_EQ(priv->pluginData[0].plugin.name, QString("BarPlugin"));
    EXPECT_EQ(priv->pluginData[1].plugin.name, QString("FooPlugin"));
    EXPECT_EQ(priv->pluginData[2].plugin.name, QString("bazplugin"));

    EXPECT_EQ(priv->dataSourceModel.rowCount(), 1);

    EXPECT_EQ(priv->eegDecoderModel.rowCount(), 2);
    EXPECT_EQ(priv->vidDecoderModel.rowCount(), 1);
    EXPECT_EQ(priv->imuDecoderModel.rowCount(), 0);

    EXPECT_EQ(priv->eegFeatExModel.rowCount(), 1);
    EXPECT_EQ(priv->vidFeatExModel.rowCount(), 0);
    EXPECT_EQ(priv->imuFeatExModel.rowCount(), 1);

    EXPECT_EQ(priv->dataSinkModel.rowCount(), 0);
    EXPECT_EQ(priv->classifierModel.rowCount(), 0);
    EXPECT_EQ(priv->outputActionModel.rowCount(), 0);
}

TEST_F(PluginManagerTest, FindElementWithIndices)
{
    auto itemHasName = [=](const QStandardItemModel *m, int p, int c,
                           const QString &name) {
        QStandardItem *item = priv->findItemWithIndices(m, p, c);
        if (!item) return false;
        return m->data(m->indexFromItem(item)).toString() == name;
    };

    manager->setSearchPath(testPluginPath);
    EXPECT_TRUE(itemHasName(&priv->eegDecoderModel, 0, 0, "BarEegDecoder"));
    EXPECT_TRUE(itemHasName(&priv->eegDecoderModel, 1, 0, "FooEegDecoder"));

    EXPECT_FALSE(itemHasName(&priv->eegDecoderModel, 0, 1, "BarVideoDecoder"));
    EXPECT_TRUE(itemHasName(&priv->vidDecoderModel, 0, 1, "BarVideoDecoder"));
}
