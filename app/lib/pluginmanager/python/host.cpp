#include <QCoreApplication>
#include "bindings/elapse.h"
#include "host.h"

namespace py = boost::python;

QMap<QObject*, py::object> pyhost::instances;

void pyhost::removeInstance(QObject *obj)
{
    instances.remove(obj);
    obj->deleteLater();
}

void pyhost::initPython()
{
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    char *name = const_cast<char*>(qPrintable(qApp->applicationName()));
    Py_SetProgramName(name);
    Py_Initialize();

    // Export our wrappers to python
    initelapse();
}

void pyhost::addParentToPythonPath(QDir dir)
{
    dir.cdUp();
    const char *path = qPrintable(dir.absolutePath());

    py::list sys_path = py::extract<py::list>(py::import("sys").attr("path"));
    if (!sys_path.contains(path))
        sys_path.append(path);
}

QMap<QString, py::object> pyhost::getClasses(const QString &moduleName)
{
    QMap<QString, py::object> classes;

    py::object module = py::import(qPrintable(moduleName));
    py::list classList = py::extract<py::list>(module.attr("classes"));
    const uint nClasses = py::len(classList);
    for (uint i = 0; i < nClasses; i++) {
        py::object cls = classList[i];
        // typecheck
        auto className = py::extract<const char*>(cls.attr("__name__"))();
        classes[className] = cls;
    }

    return classes;
}

QString pyhost::baseClassName(py::object cls)
{
    py::object base = cls.attr("__base__");
    if (py::extract<std::string>(base.attr("__module__"))() != "Boost.Python")
        return baseClassName(base);
    return QString(py::extract<const char*>(cls.attr("__name__")));
}

elapse::Signal::Type pyhost::signalType(py::object cls)
{
    if (PyObject_HasAttrString(cls.ptr(), "signalType")) {
        auto sigType = py::str(cls.attr("signalType"));
        return elapse::Signal::fromString(py::extract<const char*>(sigType));
    }
    return elapse::Signal::INVALID;
}

QObject *pyhost::extractQObject(py::object obj, const QString &cls)
{
    if (cls == "FeatureExtractor")
        return py::extract<elapse::FeatureExtractor*>(obj)();
//    else if (cls == "Classifier")
//        return py::extract<elapse::Classifier>(obj);
    return nullptr;
}
