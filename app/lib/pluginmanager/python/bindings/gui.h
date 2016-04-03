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

#ifndef PYTHON_GUI_H
#define PYTHON_GUI_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <QInputDialog>

namespace py = boost::python;


py::object getInt(const char *title, const char *label, int value = 0,
                  int min = -2147483647, int max = 2147483647, int step = 1)
{
    bool ok;
    int i = QInputDialog::getInt(nullptr, title, label, value, min, max, step, &ok);
    return ok ? py::object(i) : py::object();
}


void export_gui()
{
    using namespace boost::python;

    // Make this a sub-module of 'elapse'
    object gui(handle<>(borrowed(PyImport_AddModule("elapse.gui"))));
    scope().attr("gui") = gui;
    scope gui_scope = gui;

    def("getInt", getInt);
}

#endif // DOXYGEN
#endif // PYTHON_GUI_H
