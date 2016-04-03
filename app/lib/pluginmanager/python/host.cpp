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

#include <QCoreApplication>
#include <QxtLogger>
#include <boost/python.hpp>
#include "bindings/elapse.h"
#include "exception.h"
#include "host.h"

namespace py = boost::python;

namespace {

/*!
 * A list of classes exported by modules, keyed by the module name and
 * class name.
 */
QMap<QString, QMap<QString, py::object>> classRegistry;

/*!
 * A cache to keep a reference to boost::python::object%s, keyed by their
 * corresponding QObject pointers. This keeps a reference to the python
 * objects until the C++ shared pointer is released, at which point
 * removeInstance() removes the python object from this cache.
 */
QMap<QObject*, py::object> instances;

}

namespace elapse { namespace plugin { namespace python {

using data::Signal;

/*!
 * Add the python \a instance corresponding to the given \a obj to the
 * internal cache.
 */
void storeInstance(QObject *obj, py::object instance)
{
    instances[obj] = instance;
}

/*!
 * Remove the python object corresponding to the given \a obj from the
 * internal cache.
 */
void removeInstance(QObject *obj)
{
    instances.remove(obj);
}

/*!
 * Initialise the python interpreter and register the elapse bindings.
 */
void initPython()
{
    if (Py_IsInitialized())
        return;

    static QByteArray appName = qApp->applicationName().toLatin1();
    Py_SetProgramName(appName.data());
    PyImport_AppendInittab("elapse", &initelapse);
    Py_Initialize();
}

/*!
 * Add the parent directory of the given \a dir to python's search path.
 */
void addParentToPythonPath(QDir dir)
{
    dir.cdUp();
    auto path = py::str(dir.absolutePath().toStdString());

    py::list sys_path = py::extract<py::list>(py::import("sys").attr("path"));
    if (!sys_path.contains(path))
        sys_path.append(path);
}

/*!
 * Called from python as a class decorator. Stores the given \a cls in the
 * internal class registry keyed by its module name and class name.
 */
void registerClass(py::object cls)
{
    QString moduleName(py::extract<const char*>(cls.attr("__module__")));
    QString className(py::extract<const char*>(cls.attr("__name__")));

    // If the class is defined in a submodule, store only the top-level module
    moduleName = moduleName.left(moduleName.indexOf('.'));

    // TODO: check cls is a valid element class
    classRegistry[moduleName][className] = cls;
}

/*!
 * Load the python module with the given \a moduleName and get the list of
 * elapse::elements classes that it exports.
 * \return a mapping from class names to python class objects.
 * \see registerClass
 */
QMap<QString, py::object> getClasses(const QString &moduleName)
{
    py::object module = py::import(py::str(moduleName.toStdString()));
    return classRegistry[moduleName];
}

/*!
 * \return the name of the elapse::elements base class that the given \a cls
 * inherits from.
 */
QString baseClassName(py::object cls)
{
    py::object base = cls.attr("__base__");
    if (py::extract<std::string>(base.attr("__module__"))() != "Boost.Python")
        return baseClassName(base);
    return QString(py::extract<const char*>(cls.attr("__name__")));
}

/*!
 * \return the value of the "signalType" attribute of the given \a cls
 * (if any), otherwise Signal::INVALID.
 */
Signal::Type signalType(py::object cls)
{
    if (PyObject_HasAttrString(cls.ptr(), "signalType")) {
        auto sigType = py::str(cls.attr("signalType"));
        return Signal::fromString(py::extract<const char*>(sigType));
    }
    return Signal::INVALID;
}

/*!
 * Extract a QObject pointer from the given python \a obj. You need to pass
 * the name of the appropriate baseClass() as \a cls.
 * \return the QObject pointer, or null if \a obj is not an instance of \a cls.
 */
QObject *extractQObject(py::object obj, const QString &cls)
{
    if (cls == "FeatureExtractor") {
        py::extract<BaseFeatureExtractorWrap*> basefx(obj);
        py::extract<FeatureExtractorWrap*> fx(obj);
        if (basefx.check())
            return basefx();
        else
            return fx();
    } else if (cls == "Classifier")
        return py::extract<ClassifierWrap*>(obj);
    else if (cls == "OutputAction")
        return py::extract<OutputActionWrap*>(obj);
    else if (cls == "DataSink")
        return py::extract<DataSinkWrap*>(obj);
    return nullptr;
}

/*!
 * \return the details of the current python::Exception. It is only valid to
 * call this function from within a `boost::python::error_already_set` exception
 * handler.
 *
 * Adapted from http://thejosephturner.com/blog/post/embedding-python-in-c-applications-with-boostpython-part-2/
 */
Exception getException()
{
    Exception exc;
    exc.type = "Unknown Python exception";

    PyObject *type = nullptr, *value = nullptr, *traceback = nullptr;
    PyErr_Fetch(&type, &value, &traceback);

    if (type) {
        py::handle<> hType(type);
        py::str strType(py::object(hType).attr("__name__"));
        py::extract<const char*> extractor(strType);
        if (extractor.check())
            exc.type = extractor();
    }

    if (value) {
        py::handle<> hValue(value);
        py::str strValue(hValue);
        py::extract<const char*> extractor(strValue);
        if (extractor.check())
            exc.value = extractor();
    }

    if (traceback) {
        py::handle<> hTraceback(traceback);
        py::object format_tb(py::import("traceback").attr("format_tb"));
        py::list lines(format_tb(hTraceback));
        for (int i = 0; i < py::len(lines); i++) {
            py::extract<const char*> extractor(lines[i]);
            if (extractor.check()) {
                QString line = extractor();
                exc.traceback.append(line.split('\n'));
            }
        }
    }

    return exc;
}

/*!
 * Get the details of the current python::Exception and write them to the
 * `qxtLogger`. The traceback is written at Debug level and the error message
 * is written at Error level.
 */
void logException()
{
    Exception exc = getException();

    qxtLog->debug("Python traceback (most recent call last):");
    for (auto &line : exc.traceback)
        if (!line.isEmpty())
            qxtLog->debug(line);

    qxtLog->error(exc.type + ": " + exc.value);
}

}}} // namespace elapse::plugin::python
