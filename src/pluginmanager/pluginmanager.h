#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>

class QStandardItem;
class QStandardItemModel;

namespace Ui {
class PluginManager;
}

class PluginManager : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QDir searchPath MEMBER _path WRITE setSearchPath)

public:
    explicit PluginManager(QDir searchPath = QDir(), QWidget *parent = 0);
    ~PluginManager();

    void setSearchPath(QDir path);

    QStandardItemModel *model() const;

private:
    QStandardItem *createInterfaceItem(const QString &iid);
    QStandardItem *createPluginItem(const QString &name, const QFileInfo &file);
    QStandardItem *createImplementationItem(const QMetaObject &obj);
    void attachViews();

    QDir _path;
    QStandardItemModel *_model;
    Ui::PluginManager *ui;
};

#endif // PLUGINMANAGER_H
