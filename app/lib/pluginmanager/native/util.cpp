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
#include "elapse/plugin.h"
#include "pluginmanager_global.h"
#include "util.h"

using elapse::data::Signal;


static const QMetaObject *baseClass(const QMetaObject *obj)
{
    const QMetaObject *super = obj->superClass();
    if (super && super != &QObject::staticMetaObject)
        return baseClass(super);
    return obj;
}

static QString stripNamespace(const char *ident)
{
    QString s(ident);
    return s.remove(0, s.lastIndexOf(':') + 1);
}

static Signal::Type signalType(const QMetaObject &obj)
{
    int typeIdx = obj.indexOfClassInfo("SignalType");
    if (typeIdx >= 0) {
        const char *type = obj.classInfo(typeIdx).value();
        return Signal::fromString(type);
    }
    return Signal::INVALID;
}


namespace elapse { namespace plugin { namespace native {


template<class T>
bool getPluginDataFrom(T &plugin, PluginData &data)
{
    data.plugin.name = plugin.metaData()["className"].toString();

    QObject *pluginInstance = plugin.instance();
    auto factory = qobject_cast<plugin::Interface*>(pluginInstance);
    if (!factory)
        return false;

    for (const QMetaObject &obj : factory->classes()) {
        ClassInfo cls;
        cls.elementClass = stripNamespace(baseClass(&obj)->className());
        cls.signalType = signalType(obj);
        cls.className = stripNamespace(obj.className());
        data.classes.append(cls);
    }

    return true;
}

// Explicitly instantiate template with relevant Qt plugin types
template bool getPluginDataFrom(const QStaticPlugin &plugin, PluginData &data);
template bool getPluginDataFrom(QPluginLoader &plugin, PluginData &data);

QObject *instantiateClassFrom(QObject *pluginInstance, const QString &className)
{
    auto factory = qobject_cast<plugin::Interface*>(pluginInstance);
    if (!factory)
        return nullptr;

    for (const QMetaObject &obj : factory->classes()) {
        if (stripNamespace(obj.className()) == className) {
            QObject *object = obj.newInstance();
            if (object)
                return object;
        }
    }

    return nullptr;
}

}}} // namespace elapse::plugin::native
