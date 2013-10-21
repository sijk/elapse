#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDir>
#include <QStandardItemModel>

class PluginManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDir searchPath MEMBER _path WRITE setSearchPath)

public:
    explicit PluginManager(QDir searchPath, QObject *parent = 0);

    void setSearchPath(QDir path);

    QStandardItemModel *model() const;

private:
    QStandardItem *createInterfaceItem(const QString &iid);
    QStandardItem *createPluginItem(const QString &name, const QFileInfo &file);

    QDir _path;
    QStandardItemModel *_model;
};

#endif // PLUGINMANAGER_H
