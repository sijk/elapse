#ifndef PYTHON_HOST_H
#define PYTHON_HOST_H

#include <boost/python.hpp>
#include <QMap>
#include <QDir>
#include "elapse/datatypes.h"

namespace elapse { namespace plugin {

/*!
 * \brief Helper functions for working with plugins implemented in Python.
 */

namespace python {

namespace py = boost::python;

extern QMap<QObject*, py::object> instances;

void removeInstance(QObject *obj);

void initPython();

void addParentToPythonPath(QDir dir);

QMap<QString, py::object> getClasses(const QString &moduleName);

QString baseClassName(py::object cls);

data::Signal::Type signalType(py::object cls);

QObject *extractQObject(py::object obj, const QString &cls);

}}} // namespace elapse::plugin::python

#endif // PYTHON_HOST_H
