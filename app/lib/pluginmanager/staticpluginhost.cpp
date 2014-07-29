#include <QPluginLoader>
#include <QStaticPlugin>
#include <QxtLogger>
#include "elapse/plugin.h"
#include "native/util.h"
#include "staticpluginhost.h"

Q_IMPORT_PLUGIN(CorePlugin)


QList<PluginData> StaticPluginHost::searchForPluginsIn(QDir &dir)
{
    Q_UNUSED(dir);
    QList<PluginData> pluginData;
    QVector<QStaticPlugin> plugins = QPluginLoader::staticPlugins();

    for (const QStaticPlugin &plugin : plugins) {
        PluginData data;
        data.plugin.host = PluginHostID::Static;
        data.plugin.name = plugin.metaData()["className"].toString();

        QObject *instance = plugin.instance();
        auto factory = qobject_cast<elapse::PluginInterface*>(instance);

        if (!factory) {
            qxtLog->debug("Could not get static plugin instance for",
                          data.plugin.name);
            continue;
        }

        for (const QMetaObject &obj : factory->classes()) {
            ClassInfo cls;
            cls.elementClass = stripNamespace(baseClass(&obj)->className());
            cls.signalType = signalType(obj);
            cls.className = obj.className();
            data.classes.append(cls);
        }

        pluginData.append(data);
    }

    return pluginData;
}

PluginData StaticPluginHost::getInfo(const QString &pluginPath)
{
    Q_UNUSED(pluginPath);
    return PluginData();
}

QObject *StaticPluginHost::instantiateClass(const PluginInfo &pluginInfo,
                                            const ClassInfo &classInfo)
{
    QVector<QStaticPlugin> plugins = QPluginLoader::staticPlugins();

    for (const QStaticPlugin &plugin : plugins) {
        if (plugin.metaData()["className"].toString() != pluginInfo.name)
            continue;

        QObject *instance = plugin.instance();
        auto factory = qobject_cast<elapse::PluginInterface*>(instance);

        if (!factory) {
            qxtLog->debug("Could not get static plugin instance for",
                          pluginInfo.name);
            continue;
        }

        for (const QMetaObject &obj : factory->classes()) {
            if (obj.className() == classInfo.className) {
                QObject *object = obj.newInstance();
                if (object)
                    return object;
            }
        }
    }

    return nullptr;
}

