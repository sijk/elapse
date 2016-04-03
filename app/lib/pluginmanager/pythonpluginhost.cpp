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

#include <QDir>
#include <boost/python.hpp>
#include "pythonpluginhost.h"
#include "python/host.h"
#include "python/exception.h"

namespace elapse { namespace plugin {

/*!
 * Create a new PythonPluginHost and initialize the Python interpreter.
 */
PythonHost::PythonHost()
{
    python::initPython();
}

/*!
 * Import the Python package at \a pluginPath and extract the list of classes.
 */
PluginData PythonHost::getInfo(const QString &pluginPath)
{
    PluginData data;
    QDir dir(pluginPath);
    QString moduleName(dir.dirName());

    if (!dir.exists("__init__.py"))
        return data;

    try {
        data.plugin.host = HostID::Python;
        data.plugin.path = pluginPath;
        data.plugin.name = moduleName;

        python::addParentToPythonPath(dir);
        auto classes = python::getClasses(moduleName);

        for (auto i = classes.cbegin(); i != classes.cend(); i++) {
            ClassInfo cls;
            cls.elementClass = python::baseClassName(i.value());
            cls.signalType = python::signalType(i.value());
            cls.className = i.key();
            data.classes.append(cls);
        }
    } catch (const boost::python::error_already_set &) {
        python::logException();
        return PluginData();
    }

    return data;
}

QObject *PythonHost::instantiateClass(const PluginInfo &plugin,
                                      const ClassInfo &cls)
{
    QObject *obj;
    QDir dir(plugin.path);

    try {
        auto classes = python::getClasses(dir.dirName());
        boost::python::object pyobj = classes[cls.className]();
        obj = python::extractQObject(pyobj, cls.elementClass);
        python::storeInstance(obj, pyobj);
    } catch (const boost::python::error_already_set&) {
        python::logException();
        return nullptr;
    }

    return obj;
}

/*!
 * \return an elements::ElementDeleter that will remove objects from the
 * internal cache of Python instances.
 */
elements::ElementDeleter PythonHost::deleter()
{
    return &python::removeInstance;
}

}} // namespace elapse::plugin
