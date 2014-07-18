#ifndef PYTHON_UTIL_H
#define PYTHON_UTIL_H

#include <boost/python.hpp>
#include <QMap>
#include <QDir>
#include "elapse/sampletypes.h"

namespace pyhost {

using boost::python::object;

extern QMap<QObject*, object> instances;

void removeInstance(QObject *obj);

void initPython();

void addParentToPythonPath(QDir dir);

QMap<QString, object> getClasses(const QString &moduleName);

QString baseClassName(object cls);

elapse::Signal::Type signalType(object cls);

QObject *extractQObject(object obj, const QString &cls);

} // namespace python

#endif // PYTHON_UTIL_H
