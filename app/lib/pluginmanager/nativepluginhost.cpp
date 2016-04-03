/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

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
