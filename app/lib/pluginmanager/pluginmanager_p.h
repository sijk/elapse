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
    QMap<PluginHostID, PluginHost*> hosts;
    QList<PluginData> pluginData;

    void searchForPlugins();
    void populateModels();
    void attachModelViews();

    typedef QPair<const PluginInfo*, const ClassInfo*> ElementInfo;
    typedef QMap<QString, ElementInfo> ElementSetInfo;

    ElementSetInfo getSelectedElements() const;
    ElementSetInfo getSavedElements() const;
    ElementSetPtr createElements(const ElementSetInfo &info);
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
        elapse::Signal::Type signalType;
        QString elementName;
    };
    QList<ElementData> elements;

private:
    PluginManager * const q_ptr;
    Q_DECLARE_PUBLIC(PluginManager)
};

#endif // PLUGINMANAGER_P_H
