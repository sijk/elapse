#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

#include "pluginmanager.h"

class QStandardItem;
class QStandardItemModel;
class QTreeView;
namespace Ui { class PluginManager; }


class PluginManagerPrivate
{
public:
    PluginManagerPrivate(PluginManager *q);
    ~PluginManagerPrivate();
    static PluginManagerPrivate *expose(PluginManager *manager);

    struct ClassInfo;
    typedef void (PluginManagerPrivate::*ElementLoader)(ElementSetPtr);

    void setSearchPath(QDir newPath);

    static QStandardItem *createElementTypeItem(const QString &name);
    static QStandardItem *createPluginItem(const QString &name,
                                           const QFileInfo &file);
    static QStandardItem *createElementItem(const QMetaObject &obj);
    static const QMetaObject *baseClass(const QMetaObject *obj);
    static QStandardItem *childWithText(const QStandardItem *item,
                                        const QString &name);
    void attachViews();

    ElementSetPtr loadSelectedElements();
    ElementSetPtr loadSavedElements();
    ElementSetPtr doLoadElements(ElementLoader loader);

    void loadElementSetFromSelection(ElementSetPtr elements);
    void loadElementSetFromSettings(ElementSetPtr elements);

    template<class ElementType>
    static void loadElement(ElementType &element, ClassInfo info);

    static ClassInfo getSelectedElement(QTreeView *tree);
    static ClassInfo getSavedElement(QString elementName);

    void saveSelectedElements();
    void selectSavedElements();

    Ui::PluginManager *ui;
    QDir path;
    QStandardItemModel *model;
    static const QString pathSetting;
    static const QString classSetting;
};

struct PluginManagerPrivate::ClassInfo
{
    QString pluginPath;
    QString className;
};

#endif // PLUGINMANAGER_P_H
