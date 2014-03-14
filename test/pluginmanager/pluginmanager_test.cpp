#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QStandardItemModel>
#include <QxtLogger>
#include "../test_utils.h"

#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "pluginfilterproxymodel.h"

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


TEST_F(PluginManagerTest, SetSearchPath)
{
    QDir newPath("/tmp");
    manager->setSearchPath(newPath);
    EXPECT_EQ(manager->searchPath(), newPath);
}

TEST_F(PluginManagerTest, PopulatePluginModel)
{
    auto model = priv->model;
    ASSERT_NE(model, nullptr);

    // [root]
    //     DataSource
    //         FooPlugin
    //             FooDummySource
    //     SampleDecoder
    //         BarPlugin
    //             BarEegDecoder
    //             BarVideoDecoder
    //         FooPlugin
    //             FooEegDecoder

    ASSERT_EQ(model->rowCount(), 2);
    auto dataSrcIdx = model->index(0, 0);
    auto sampDecIdx = model->index(1, 0);
    EXPECT_EQ(model->data(dataSrcIdx).toString(), "DataSource");
    EXPECT_EQ(model->data(sampDecIdx).toString(), "SampleDecoder");

    ASSERT_EQ(model->rowCount(dataSrcIdx), 1);
    auto fooPluginSrcIdx = model->index(0, 0, dataSrcIdx);
    EXPECT_EQ(model->data(fooPluginSrcIdx).toString(), "FooPlugin");

    ASSERT_EQ(model->rowCount(fooPluginSrcIdx), 1);
    auto fooSrcIdx = model->index(0, 0, fooPluginSrcIdx);
    EXPECT_EQ(model->data(fooSrcIdx).toString(), "FooDummySource");

    ASSERT_EQ(model->rowCount(sampDecIdx), 2);
    auto barPluginDecIdx = model->index(0, 0, sampDecIdx);
    auto fooPluginDecIdx = model->index(1, 0, sampDecIdx);
    EXPECT_EQ(model->data(barPluginDecIdx).toString(), "BarPlugin");
    EXPECT_EQ(model->data(fooPluginDecIdx).toString(), "FooPlugin");

    ASSERT_EQ(model->rowCount(fooPluginDecIdx), 1);
    auto fooEegIdx = model->index(0, 0, fooPluginDecIdx);
    EXPECT_EQ(model->data(fooEegIdx).toString(), "FooEegDecoder");

    ASSERT_EQ(model->rowCount(barPluginDecIdx), 2);
    auto barEegIdx = model->index(0, 0, barPluginDecIdx);
    auto barVideoIdx = model->index(1, 0, barPluginDecIdx);
    EXPECT_EQ(model->data(barEegIdx).toString(), "BarEegDecoder");
    EXPECT_EQ(model->data(barVideoIdx).toString(), "BarVideoDecoder");
}

TEST_F(PluginManagerTest, ProxyModelForEegDecoders)
{
    PluginFilterProxyModel proxy("SampleDecoder", Signal::EEG);
    proxy.setSourceModel(priv->model);

    // [root]
    //     SampleDecoder
    //         BarPlugin
    //             BarEegDecoder
    //         FooPlugin
    //             FooEegDecoder

    ASSERT_EQ(proxy.rowCount(), 1);
    auto sampDecIdx = proxy.index(0, 0);
    EXPECT_EQ(proxy.data(sampDecIdx).toString(), "SampleDecoder");

    ASSERT_EQ(proxy.rowCount(sampDecIdx), 2);
    auto barPluginDecIdx = proxy.index(0, 0, sampDecIdx);
    auto fooPluginDecIdx = proxy.index(1, 0, sampDecIdx);
    EXPECT_EQ(proxy.data(barPluginDecIdx).toString(), "BarPlugin");
    EXPECT_EQ(proxy.data(fooPluginDecIdx).toString(), "FooPlugin");

    ASSERT_EQ(proxy.rowCount(fooPluginDecIdx), 1);
    auto fooEegIdx = proxy.index(0, 0, fooPluginDecIdx);
    EXPECT_EQ(proxy.data(fooEegIdx).toString(), "FooEegDecoder");

    ASSERT_EQ(proxy.rowCount(barPluginDecIdx), 1);
    auto barEegIdx = proxy.index(0, 0, barPluginDecIdx);
    EXPECT_EQ(proxy.data(barEegIdx).toString(), "BarEegDecoder");
}

TEST_F(PluginManagerTest, ProxyModelForVideoDecoders)
{
    PluginFilterProxyModel proxy("SampleDecoder", Signal::VIDEO);
    proxy.setSourceModel(priv->model);

    // [root]
    //     SampleDecoder
    //         BarPlugin
    //             BarVideoDecoder
    //         FooPlugin

    ASSERT_EQ(proxy.rowCount(), 1);
    auto sampDecIdx = proxy.index(0, 0);
    EXPECT_EQ(proxy.data(sampDecIdx).toString(), "SampleDecoder");

    ASSERT_EQ(proxy.rowCount(sampDecIdx), 2);
    auto barPluginDecIdx = proxy.index(0, 0, sampDecIdx);
    auto fooPluginDecIdx = proxy.index(1, 0, sampDecIdx);
    EXPECT_EQ(proxy.data(barPluginDecIdx).toString(), "BarPlugin");
    EXPECT_EQ(proxy.data(fooPluginDecIdx).toString(), "FooPlugin");

    ASSERT_EQ(proxy.rowCount(barPluginDecIdx), 1);
    auto barEegIdx = proxy.index(0, 0, barPluginDecIdx);
    EXPECT_EQ(proxy.data(barEegIdx).toString(), "BarVideoDecoder");
}

TEST_F(PluginManagerTest, ProxyModelForDataSources)
{
    PluginFilterProxyModel proxy("DataSource", Signal::INVALID);
    proxy.setSourceModel(priv->model);

    // [root]
    //     DataSource
    //         FooPlugin
    //             FooDummySource

    ASSERT_EQ(proxy.rowCount(), 1);
    auto dataSrcIdx = proxy.index(0, 0);
    EXPECT_EQ(proxy.data(dataSrcIdx).toString(), "DataSource");

    ASSERT_EQ(proxy.rowCount(dataSrcIdx), 1);
    auto fooPluginSrcIdx = proxy.index(0, 0, dataSrcIdx);
    EXPECT_EQ(proxy.data(fooPluginSrcIdx).toString(), "FooPlugin");

    ASSERT_EQ(proxy.rowCount(fooPluginSrcIdx), 1);
    auto fooSrcIdx = proxy.index(0, 0, fooPluginSrcIdx);
    EXPECT_EQ(proxy.data(fooSrcIdx).toString(), "FooDummySource");
}

