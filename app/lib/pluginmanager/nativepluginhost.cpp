#include <QPluginLoader>
#include <QxtLogger>
#include "native/util.h"
#include "nativepluginhost.h"

namespace elapse { namespace plugin {

/*!
 * Retrieve metadata from the plugin at \a pluginPath, if it is a native plugin.
 */
PluginData NativeHost::getInfo(const QString &pluginPath)
{
    if (!QLibrary::isLibrary(pluginPath))
        return PluginData();

    PluginData data;
    data.plugin.host = HostID::Native;
    data.plugin.path = pluginPath;

    QPluginLoader loader(pluginPath);

    if (!native::getPluginDataFrom(loader, data))
        qxtLog->debug(loader.errorString());

    return data;
}

QObject *NativeHost::instantiateClass(const PluginInfo &pluginInfo,
                                      const ClassInfo &classInfo)
{
    QPluginLoader loader(pluginInfo.path);
    QObject *instance = native::instantiateClassFrom(loader.instance(),
                                                     classInfo.className);
    if (!instance)
        qxtLog->debug(loader.errorString());

    return instance;
}

}} // namespace elapse::plugin
