#include <QCoreApplication>
#include <QxtLogger>
#include "bindings/elapse.h"
#include "exception.h"
#include "host.h"

namespace py = boost::python;

QMap<QObject*, py::object> pyhost::instances;

void pyhost::removeInstance(QObject *obj)
{
    instances.remove(obj);
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

/*
 * Adapted from http://thejosephturner.com/blog/post/embedding-python-in-c-applications-with-boostpython-part-2/
 */
PythonException getPythonException()
{
    PythonException exc;
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

void logPythonException()
{
    PythonException exc = getPythonException();

    qxtLog->debug("Python traceback (most recent call last):");
    for (auto &line : exc.traceback)
        if (!line.isEmpty())
            qxtLog->debug(line);

    qxtLog->error(exc.type + ": " + exc.value);
}
