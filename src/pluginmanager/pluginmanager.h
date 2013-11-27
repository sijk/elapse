#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>

class QStandardItem;
class QStandardItemModel;
class ElementSet;

namespace Ui {
class PluginManager;
}

class PluginManager : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QDir searchPath MEMBER path WRITE setSearchPath)

public:
    explicit PluginManager(QWidget *parent = 0);
    ~PluginManager();

    void setSearchPath(QDir newPath);
    void loadPlugins();

signals:
    void pluginsLoaded(ElementSet* elements);

private slots:
    void loadSelectedElementsFromPlugins();

private:
    QStandardItem *createElementItem(const QString &name);
    QStandardItem *createPluginItem(const QString &name, const QFileInfo &file);
    QStandardItem *createClassItem(const QMetaObject &obj);
    void attachViews();

    static const QMetaObject *baseClass(const QMetaObject *obj);
    static QStandardItem *childWithText(const QStandardItem *item,
                                        const QString &name);

    QDir path;
    QStandardItemModel *model;
    Ui::PluginManager *ui;
};

#endif // PLUGINMANAGER_H
