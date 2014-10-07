#ifndef PYTHON_HOST_H
#define PYTHON_HOST_H

#include <boost/python/object.hpp>
#include <QMap>
#include <QDir>
#include "elapse/datatypes.h"

namespace elapse { namespace plugin {

/*!
 * \brief Helper functions for working with plugins implemented in Python.
 */

namespace python {

using boost::python::object;

void storeInstance(QObject *obj, object instance);
void removeInstance(QObject *obj);

void initPython();

void addParentToPythonPath(QDir dir);

void registerClass(object cls);

QMap<QString, object> getClasses(const QString &moduleName);

QString baseClassName(object cls);

data::Signal::Type signalType(object cls);

QObject *extractQObject(object obj, const QString &cls);

}}} // namespace elapse::plugin::python

#endif // PYTHON_HOST_H
