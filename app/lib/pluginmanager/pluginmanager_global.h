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

#ifndef PLUGINMANAGER_GLOBAL_H
#define PLUGINMANAGER_GLOBAL_H

#include <QtCore>
#include "elapse/datatypes.h"

namespace elapse { namespace plugin {

/*!
 * \brief The HostID enum lists the available plugin::Host%s.
 */
enum class HostID
{
    Static,
    Native,
    Python,
};

/*!
 * \brief The PluginInfo struct contains information to uniquely identify
 * a plugin.
 */
struct PluginInfo
{
    QString name;                    ///< The name of the plugin
    QString path;                    ///< Absolute path to the plugin file
    HostID host;               ///< Which PluginHost can load this plugin
};

/*!
 * \brief The ClassInfo struct contains information to uniquely identify
 * a class within a particular plugin.
 */
struct ClassInfo
{
    QString elementClass;            ///< The element base class this class inherits from
    data::Signal::Type signalType;   ///< The signal type this class works with (if specified)
    QString className;               ///< The name of the class
};

/*!
 * \brief The PluginData struct contains information about all of the classes
 * provided by a plugin.
 */
struct PluginData
{
    PluginInfo plugin;               ///< Info about the plugin
    QList<ClassInfo> classes;        ///< Info about the classes the plugin provides
};

}} // namespace elapse::plugin

#endif // PLUGINMANAGER_GLOBAL_H
