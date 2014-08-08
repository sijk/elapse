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
