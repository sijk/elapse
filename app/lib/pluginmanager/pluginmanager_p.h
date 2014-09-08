#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

#include <QStandardItemModel>
#include "pluginmanager.h"
#include "ui_pluginmanager.h"
#include "pluginmanager_global.h"
#include "pluginhost.h"

namespace elapse { namespace plugin {

class ManagerPrivate
{
public:
    ManagerPrivate(plugin::Manager *q);
    ~ManagerPrivate();

    static ManagerPrivate *expose(plugin::Manager *manager);

    Ui::PluginManager ui;
    QDir searchPath;
    QMap<HostID, Host*> hosts;
    QList<PluginData> pluginData;

    void searchForPlugins();
    void populateModels();
    void attachModelViews();

    typedef QPair<const PluginInfo*, const ClassInfo*> ElementInfo;
    typedef QMap<QString, ElementInfo> ElementSetInfo;

    ElementSetInfo getSelectedElements() const;
    ElementSetInfo getSavedElements() const;
    elements::ElementSetPtr createElements(const ElementSetInfo &info);
    void selectElements(const ElementSetInfo &info);
    void saveElements(const ElementSetInfo &info);

    template<class T>
    void createElement(QSharedPointer<T> &element, const ElementInfo &info);

    QStandardItem *findItemWithIndices(const QStandardItemModel *model,
                                       int pluginIndex, int classIndex);

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

    struct ElementData {
        QStandardItemModel *model;
        QTreeView *tree;
        QString elementClass;
        elapse::data::Signal::Type signalType;
        QString elementName;
    };
    QList<ElementData> elements;

private:
    plugin::Manager * const q_ptr;
    Q_DECLARE_PUBLIC(plugin::Manager)
};

}} // namespace elapse::plugin

#endif // PLUGINMANAGER_P_H
