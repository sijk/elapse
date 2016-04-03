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

#ifndef PYTHON_LOG_H
#define PYTHON_LOG_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <boost/python/raw_function.hpp>
#include <QxtLogger>

namespace py = boost::python;


inline QVariantList tupleToStringVariantList(const py::tuple &args)
{
    QVariantList messages;
    for (int i = 0; i < py::len(args); i++)
        messages << QString(py::extract<const char*>(args[i]));
    return messages;
}

py::object trace(py::tuple args, py::dict)
{
    qxtLog->trace(tupleToStringVariantList(args));
    return {};
}

py::object debug(py::tuple args, py::dict)
{
    qxtLog->debug(tupleToStringVariantList(args));
    return {};
}

py::object info(py::tuple args, py::dict)
{
    qxtLog->info(tupleToStringVariantList(args));
    return {};
}

py::object warning(py::tuple args, py::dict)
{
    qxtLog->warning(tupleToStringVariantList(args));
    return {};
}

py::object error(py::tuple args, py::dict)
{
    qxtLog->error(tupleToStringVariantList(args));
    return {};
}


void export_log()
{
    using namespace boost::python;

    // Make this a sub-module of 'elapse'
    object log(handle<>(borrowed(PyImport_AddModule("elapse.log"))));
    scope().attr("log") = log;
    scope log_scope = log;

    def("trace", raw_function(trace));
    def("debug", raw_function(debug));
    def("info", raw_function(info));
    def("warning", raw_function(warning));
    def("error", raw_function(error));
}

#endif // DOXYGEN
#endif // PYTHON_LOG_H
