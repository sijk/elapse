#include <QCoreApplication>
#include <QPluginLoader>
#include <QSet>
#include "pluginloader.h"
#include "plugin.h"

#include <QDebug>

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
    search(QCoreApplication::instance()->applicationDirPath() + "/plugins");
}

QStringList PluginLoader::interfaces() const
{
    QSet<QString> ifaces;
    foreach (auto info, pluginInfo)
        ifaces.insert(info["IID"].toString());
    return ifaces.toList();
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

QObject *PluginLoader::create(const QString &key)
{
    QPluginLoader loader(pluginPath[key]);
    auto factory = static_cast<GenericPlugin*>(loader.instance());

    if (factory)
        return factory->create(key);

    return 0;
}

void PluginLoader::search(QDir path)
{
    qDebug() << "Searching" << path.absolutePath();
    foreach (QString fileName, path.entryList(QDir::Files)) {
        qDebug() << "  Examining" << fileName;

        QPluginLoader loader(path.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        QString iid = loader.metaData()["IID"].toString();
        qDebug() << "    Name:" << loader.metaData()["className"].toString();
        qDebug() << "    IID: " << iid;
        qDebug() << "    Keys:";

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
                qDebug() << "      " << key;
                pluginInfo[key] = loader.metaData();
                pluginPath[key] = path.absoluteFilePath(fileName);
            }
        }
        loader.unload();
    }
}
