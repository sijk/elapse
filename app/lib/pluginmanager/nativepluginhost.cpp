#include <QPluginLoader>
#include <QxtLogger>
#include "native/util.h"
#include "nativepluginhost.h"


/*!
 * Retrieve metadata from the plugin at \a pluginPath, if it is a native plugin.
 */
PluginData NativePluginHost::getInfo(const QString &pluginPath)
{
    if (!QLibrary::isLibrary(pluginPath))
        return PluginData();

    PluginData data;
    data.plugin.host = PluginHostID::Native;
    data.plugin.path = pluginPath;

    QPluginLoader loader(pluginPath);

    if (!getPluginDataFrom(loader, data))
        qxtLog->debug(loader.errorString());

    return data;
}

QObject *NativePluginHost::instantiateClass(const PluginInfo &pluginInfo,
                                            const ClassInfo &classInfo)
{
    QPluginLoader loader(pluginInfo.path);
    QObject *instance = instantiateClassFrom(loader.instance(),
                                             classInfo.className);
    if (!instance)
        qxtLog->debug(loader.errorString());

    return instance;
}
