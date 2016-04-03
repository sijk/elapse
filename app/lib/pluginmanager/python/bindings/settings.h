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

#ifndef PYTHON_SETTINGS_H
#define PYTHON_SETTINGS_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <QSettings>

namespace py = boost::python;


template<class T>
T value(const std::string &key)
{
    return QSettings().value(key.c_str()).value<T>();
}

template<class T>
void setValue(const std::string &key, const T &value)
{
    QSettings().setValue(key.c_str(), QVariant::fromValue(value));
}

template<>
std::string value(const std::string &key)
{
    return value<QString>(key).toStdString();
}

template<>
void setValue(const std::string &key, const std::string &value)
{
    setValue(key, QString::fromStdString(value));
}


void export_settings()
{
    using namespace boost::python;

    // Make this a sub-module of 'elapse'
    object settings(handle<>(borrowed(PyImport_AddModule("elapse.settings"))));
    scope().attr("settings") = settings;
    scope settings_scope = settings;

    def("getBool", value<bool>);
    def("setBool", setValue<bool>);
    def("getInt", value<int>);
    def("setInt", setValue<int>);
    def("getStr", value<std::string>);
    def("setStr", setValue<std::string>);
    def("getFloat", value<double>);
    def("setFloat", setValue<double>);
}

#endif // DOXYGEN
#endif // PYTHON_SETTINGS_H
