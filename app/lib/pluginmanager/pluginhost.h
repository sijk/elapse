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

#ifndef PLUGINHOST_H
#define PLUGINHOST_H

#include "pluginmanager_global.h"
#include "elementset.h"

namespace elapse { namespace plugin {

/*!
 * \brief The plugin::Host class is an abstract factory for loading elements
 * from plugins.
 *
 * This design allows plugins to be written in multiple languages. To add
 * support for a new language, implement a plugin::Host that can load plugins
 * written in that language and implement any required bindings for the
 * \ref pipeline-elements "element base classes".
 *
 * \ingroup plugins-int
 */

class Host
{
public:
    /*!
     * Destroy this PluginHost.
     */
    virtual ~Host() {}

    /*!
     * Search for plugins in the given \a dir. The default implementation calls
     * getInfo() with every readable file and directory in \a dir.
     */
    virtual QList<PluginData> searchForPluginsIn(QDir &dir);

    /*!
     * \return an instance of class \a cls from the given \a plugin.
     * The instance is wrapped in an elements::ElementPtr with a custom
     * deleter().
     */
    template<class T> elements::ElementPtr<T>
    instantiate(const PluginInfo &plugin, const ClassInfo &cls)
    {
        QObject *instance = instantiateClass(plugin, cls);
        return elements::ElementPtr<T>(qobject_cast<T*>(instance), deleter());
    }

protected:
    /*!
     * Analyse the plugin at \a pluginPath and return a PluginData instance
     * describing it. If the file/directory at \a pluginPath is not a plugin
     * that this PluginHost understands, return a default-constructed
     * PluginData instance.
     */
    virtual PluginData getInfo(const QString &pluginPath) = 0;

    /*!
     * Load the given \a plugin and create an instance of the given \a cls.
     */
    virtual QObject*
    instantiateClass(const PluginInfo &plugin, const ClassInfo &cls) = 0;

    /*!
     * \return a custom deleter function for the instantiated objects.
     */
    virtual elements::ElementDeleter deleter() { return std::default_delete<QObject>(); }
};

}} // namespace elapse::plugin

#endif // PLUGINHOST_H
