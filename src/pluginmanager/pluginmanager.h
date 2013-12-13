#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>
#include "elements.h"

class QStandardItem;
class QStandardItemModel;

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

signals:
    void pluginsLoaded(ElementSetPtr elements);

private slots:
    void loadSelectedElementsFromPlugins();

private:
    static QStandardItem *createElementItem(const QString &name);
    static QStandardItem *createPluginItem(const QString &name,
                                           const QFileInfo &file);
    static QStandardItem *createClassItem(const QMetaObject &obj);
    static const QMetaObject *baseClass(const QMetaObject *obj);
    static QStandardItem *childWithText(const QStandardItem *item,
                                        const QString &name);
    void attachViews();

    QDir path;
    QStandardItemModel *model;
    Ui::PluginManager *ui;
};

#endif // PLUGINMANAGER_H
