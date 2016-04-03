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
#include <QStaticPlugin>
#include <QxtLogger>
#include "native/util.h"
#include "staticpluginhost.h"

Q_IMPORT_PLUGIN(CorePlugin)

namespace elapse { namespace plugin {

/*!
 * Search for static plugins. The \a dir parameter is ignored since it is
 * meaningless in this case.
 */
QList<PluginData> StaticHost::searchForPluginsIn(QDir &dir)
{
    Q_UNUSED(dir);
    QList<PluginData> pluginData;
    QVector<QStaticPlugin> plugins = QPluginLoader::staticPlugins();

    for (const QStaticPlugin &plugin : plugins) {
        PluginData data;
        data.plugin.host = HostID::Static;

        if (!native::getPluginDataFrom(plugin, data)) {
            qxtLog->debug("Could not get static plugin instance for",
                          data.plugin.name);
            continue;
        }

        pluginData.append(data);
    }

    return pluginData;
}

/*!
 * Do nothing. File paths are not meaningful for statically-linked plugins.
 * See searchForPluginsIn() instead.
 */
PluginData StaticHost::getInfo(const QString &pluginPath)
{
    Q_UNUSED(pluginPath);
    return PluginData();
}

QObject *StaticHost::instantiateClass(const PluginInfo &pluginInfo,
                                      const ClassInfo &classInfo)
{
    QVector<QStaticPlugin> plugins = QPluginLoader::staticPlugins();

    for (const QStaticPlugin &plugin : plugins) {
        if (plugin.metaData()["className"].toString() != pluginInfo.name)
            continue;

        QObject *instance = native::instantiateClassFrom(plugin.instance(),
                                                         classInfo.className);
        if (instance)
            return instance;
        else
            qxtLog->debug("Could not instantiate", classInfo.className,
                          "from static plugin", pluginInfo.name);
    }

    return nullptr;
}

}} // namespace elapse::plugin
