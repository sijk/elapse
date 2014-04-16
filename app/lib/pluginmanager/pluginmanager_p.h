#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

#include <QStandardItemModel>
#include "pluginmanager.h"
#include "pluginmanager_def.h"
#include "ui_pluginmanager.h"


/*! \private */

class PluginManagerPrivate
{
    PluginManager * const q_ptr;
    Q_DECLARE_PUBLIC(PluginManager)

public:
    PluginManagerPrivate(PluginManager *q);
    static PluginManagerPrivate *expose(PluginManager *manager);

    void setSearchPath(QDir newPath);
    void searchForPluginsIn(QDir dir);

    static QStandardItem *createElementTypeItem(const QString &name);
    static QStandardItem *createPluginItem(const QString &name,
                                           const QFileInfo &file);
    static QStandardItem *createElementItem(const QMetaObject &obj);
    static const QMetaObject *baseClass(const QMetaObject *obj);
    static QStandardItem *childWithText(const QStandardItem *item,
                                        const QString &name);
    void attachViews();

    static ClassInfo getSelectedElement(const QTreeView *tree);

    void saveSelectedElements();
    void selectSavedElements();

    Ui::PluginManager ui;
    QStandardItemModel model;
    const QDir corePluginDir;
    QDir userPluginDir;
};

#endif // PLUGINMANAGER_P_H
