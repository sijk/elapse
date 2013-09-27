#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include <QSet>
#include <QStringList>
#include "pluginloader.h"
#include "plugin_base.h"


/*!
 * \brief The GenericPlugin class is a sort of "pseudo base class" for all plugins.
 */
class GenericPlugin : public QObject, public BasePlugin<QObject>
{
    Q_OBJECT
};


PluginLoader::PluginLoader(QObject *parent) :
    QObject(parent)
{
    setSearchPath(qApp->applicationDirPath() + "/plugins");
}

QFileInfoList PluginLoader::files() const
{
    QFileInfoList files;
    foreach (const QFileInfo &file, pluginFile) {
        if (!files.contains(file))
            files.append(file);
    }
    return files;
}

QStringList PluginLoader::interfaces() const
{
    QSet<QString> ifaces;
    foreach (const QJsonObject &info, pluginInfo)
        ifaces.insert(info["IID"].toString());
    return ifaces.toList();
}

QFileInfoList PluginLoader::filesForInterface(const QString &iid) const
{
    QFileInfoList files;
    foreach (const QString &key, pluginFile.keys()) {
        QFileInfo file = pluginFile[key];
        if (pluginInfo[key]["IID"] == iid && !files.contains(file))
            files.append(file);
    }
    return files;
}

QStringList PluginLoader::keysForInterface(const QString &iid) const
{
    QStringList keys;
    for (auto it = pluginInfo.cbegin(); it != pluginInfo.cend(); ++it) {
        if (it.value()["IID"].toString() == iid)
            keys.append(it.key());
    }
    return keys;
}

QStringList PluginLoader::keysForFile(const QFileInfo &file) const
{
    return pluginFile.keys(file);
}

QJsonObject PluginLoader::infoForFile(const QFileInfo &file) const
{
    return pluginInfo[pluginFile.keys(file).first()];
}

QJsonObject PluginLoader::infoForKey(const QString &key) const
{
    return pluginInfo[key];
}

QFileInfo PluginLoader::fileForKey(const QString &key) const
{
    return pluginFile[key];
}

QObject *PluginLoader::create(const QString &key) const
{
    QPluginLoader loader(pluginFile[key].absoluteFilePath());
    auto factory = static_cast<GenericPlugin*>(loader.instance());

    if (factory) {
        QObject *obj = factory->create(key);
        if (obj)
            emit createdKey(key);
        return obj;
    }

    return 0;
}

QDir PluginLoader::searchPath() const
{
    return path;
}

void PluginLoader::setSearchPath(QDir path)
{
    this->path = path;
    rescan();
}

void PluginLoader::rescan()
{
    pluginInfo.clear();
    pluginFile.clear();

    foreach (QFileInfo file, path.entryInfoList(QDir::Files)) {
        QPluginLoader loader(file.absoluteFilePath());
        QObject *plugin = loader.instance();
        auto factory = static_cast<GenericPlugin*>(plugin);
        if (factory) {
            foreach (const QString &key, factory->keys()) {
                if (pluginInfo.contains(key)) {
                    qDebug() << "WARNING: ignoring key" << key << "from"
                             << loader.metaData()["className"].toString()
                             << "because it clashes with a key from"
                             << pluginInfo[key]["className"].toString();
                    continue;
                }
                pluginInfo[key] = loader.metaData();
                pluginFile[key] = file;
            }
        }
        loader.unload();
    }
}
