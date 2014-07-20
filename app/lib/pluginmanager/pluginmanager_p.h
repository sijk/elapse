#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

#include <QStandardItemModel>
#include "pluginmanager.h"
#include "ui_pluginmanager.h"
#include "pluginmanager_global.h"
#include "pluginhost.h"

class PluginManagerPrivate
{
public:
    PluginManagerPrivate(PluginManager *q);
    ~PluginManagerPrivate();

    static PluginManagerPrivate *expose(PluginManager *manager);

    Ui::PluginManager ui;
    QDir searchPath;
    PluginHost *hosts[N_PLUGIN_HOSTS];
    QList<PluginData> pluginData;

    void searchForPlugins();
    void populateModels();
    void attachModelViews();

    QStandardItemModel dataSourceModel;
    QStandardItemModel dataSinkModel;
    QStandardItemModel eegDecoderModel;
    QStandardItemModel vidDecoderModel;
    QStandardItemModel imuDecoderModel;
    QStandardItemModel eegFeatExModel;
    QStandardItemModel vidFeatExModel;
    QStandardItemModel imuFeatExModel;
    QStandardItemModel classifierModel;
    QStandardItemModel outputActionModel;

private:
    PluginManager * const q_ptr;
    Q_DECLARE_PUBLIC(PluginManager)
};

#endif // PLUGINMANAGER_P_H
