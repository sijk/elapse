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
