#include <QPluginLoader>
#include <QxtLogger>
#include "elapse/plugin.h"
#include "native/util.h"
#include "nativepluginhost.h"


/*!
 * Retrieve metadata from the plugin at \a pluginPath, if it is a native plugin.
 */
PluginData NativePluginHost::getInfo(const QString &pluginPath)
{
    PluginData data;

    if (!QLibrary::isLibrary(pluginPath))
        return data;

    QPluginLoader loader(pluginPath);
    QObject *plugin = loader.instance();
    auto factory = qobject_cast<elapse::PluginInterface*>(plugin);

    if (!factory) {
        qxtLog->debug(loader.errorString());
        return data;
    }

    data.plugin.host = PluginHostID::Native;
    data.plugin.path = pluginPath;
    data.plugin.name = loader.metaData()["className"].toString();

    for (const QMetaObject &obj : factory->classes()) {
        ClassInfo cls;
        cls.elementClass = stripNamespace(baseClass(&obj)->className());
        cls.signalType = signalType(obj);
        cls.className = obj.className();
        data.classes.append(cls);
    }

    return data;
}

QObject *NativePluginHost::instantiateClass(const PluginInfo &pluginInfo,
                                            const ClassInfo &classInfo)
{
    QObject *instance;

    QPluginLoader loader(pluginInfo.path);
    QObject *plugin = loader.instance();
    auto factory = qobject_cast<elapse::PluginInterface*>(plugin);

    if (!factory) {
        qxtLog->debug(loader.errorString());
        return nullptr;
    }

    for (const QMetaObject &obj : factory->classes()) {
        if (obj.className() == classInfo.className) {
            instance = obj.newInstance();
            if (instance)
                break;
        }
    }

    return instance;
}
