#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>
#include "elements.h"

class QStandardItem;
class QStandardItemModel;
class QTreeView;

namespace Ui {
class PluginManager;
}


/*!
 * \brief The PluginManager class handles the finding and loading of plugins.
 *
 * \see \ref pluginmanager-model for a detailed description of the internal
 * data model.
 * \ingroup plugins-int
 */

class PluginManager : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QDir searchPath MEMBER path WRITE setSearchPath)

public:
    explicit PluginManager(QWidget *parent = nullptr);
    ~PluginManager();

    void setSearchPath(QDir newPath);

public slots:
    void loadPlugins();
    bool loadPluginsFromSettings();

signals:
    void pluginsLoaded(ElementSetPtr elements);

private slots:
    void loadSelectedElements();

private:
    static QStandardItem *createElementItem(const QString &name);
    static QStandardItem *createPluginItem(const QString &name,
                                           const QFileInfo &file);
    static QStandardItem *createClassItem(const QMetaObject &obj);
    static const QMetaObject *baseClass(const QMetaObject *obj);
    static QStandardItem *childWithText(const QStandardItem *item,
                                        const QString &name);
    void attachViews();

    void loadElementSetFromSelection(ElementSetPtr elements);
    void loadElementSetFromSettings(ElementSetPtr elements);

    typedef void(PluginManager::*ElementLoader)(ElementSetPtr);
    bool doLoadElements(ElementLoader loader);

    struct ClassInfo;
    ClassInfo getSelectedElement(QTreeView *tree);
    ClassInfo getSavedElement(QString elementName);

    void saveSelectedElements();
    void selectSavedElements();

    QDir path;
    QStandardItemModel *model;
    Ui::PluginManager *ui;
};

#endif // PLUGINMANAGER_H
