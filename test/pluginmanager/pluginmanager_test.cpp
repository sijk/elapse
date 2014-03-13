#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QStandardItemModel>
#include <QxtLogger>
#include "../test_utils.h"
#include "pluginmanager.h"
#include "pluginmanager_p.h"

class PluginManagerTest : public testing::Test
{
public:
    void SetUp()
    {
        qxtLog->disableAllLogLevels();

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
};


TEST_F(PluginManagerTest, CanSetSearchPath)
{
    QDir newPath("/tmp");
    manager->setSearchPath(newPath);
    EXPECT_EQ(manager->searchPath(), newPath);
}

TEST_F(PluginManagerTest, PopulatesPluginModel)
{
    auto model = priv->model;
    ASSERT_NE(model, nullptr);

    // [root]
    //     SampleDecoder
    //         FooPlugin
    //             FooEegDecoder
    //         BarPlugin
    //             BarEegDecoder

    ASSERT_EQ(model->rowCount(), 1);
    auto sampDecIdx = model->index(0, 0);
    EXPECT_EQ(model->data(sampDecIdx).toString(), "SampleDecoder");

    ASSERT_EQ(model->rowCount(sampDecIdx), 2);
    auto fooPluginIdx = model->index(1, 0, sampDecIdx);
    auto barPluginIdx = model->index(0, 0, sampDecIdx);
    EXPECT_EQ(model->data(barPluginIdx).toString(), "BarPlugin");
    EXPECT_EQ(model->data(fooPluginIdx).toString(), "FooPlugin");

    ASSERT_EQ(model->rowCount(fooPluginIdx), 1);
    auto fooEegIdx = model->index(0, 0, fooPluginIdx);
    EXPECT_EQ(model->data(fooEegIdx).toString(), "FooEegDecoder");

    ASSERT_EQ(model->rowCount(barPluginIdx), 1);
    auto barEegIdx = model->index(0, 0, barPluginIdx);
    EXPECT_EQ(model->data(barEegIdx).toString(), "BarEegDecoder");
}

