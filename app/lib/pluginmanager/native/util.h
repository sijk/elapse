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

#ifndef NATIVE_UTIL_H
#define NATIVE_UTIL_H

class QObject;
class QString;

namespace elapse { namespace plugin {

class PluginData;

/*!
 * \brief Helper functions for working with plugins implemented in C++.
 */
namespace native {

/*!
 * Inspect the given \a plugin and extract its plugin \a data. The \a plugin
 * may be an instance of either QStaticPlugin or QPluginLoader.
 * \return false if the \a plugin could not be inspected, otherwise true.
 */
template<class T> bool getPluginDataFrom(T &plugin, PluginData &data);

/*!
 * Create an instance of the class \a className from the given
 * \a pluginInstance.
 * \return the instance, or null on failure.
 */
QObject *instantiateClassFrom(QObject *pluginInstance, const QString &className);

}}} // namespace elapse::plugin::native

#endif // NATIVE_UTIL_H
