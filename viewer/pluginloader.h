#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>
#include <QDir>
#include <QHash>
#include <QStringList>
#include <QJsonObject>

class PluginLoader : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = 0);

    QStringList interfaces() const;
    QStringList keysForInterface(const QString &iid) const;
    QObject *create(const QString &key);

private:
    void search(QDir path);
    QHash<QString,QJsonObject> pluginInfo;
    QHash<QString,QString> pluginPath;
};

#endif // PLUGINLOADER_H
