#include <QCoreApplication>
#include <QxtLogger>
#include "bindings/elapse.h"
#include "exception.h"
#include "host.h"

namespace elapse { namespace plugin { namespace python {

using data::Signal;

/*!
 * A cache to keep a reference to boost::python::object%s, keyed by their
 * corresponding QObject pointers. This keeps a reference to the python
 * objects until the C++ shared pointer is released, at which point
 * removeInstance() removes the python object from this cache.
 */
QMap<QObject*, py::object> instances;

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
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    char *name = const_cast<char*>(qPrintable(qApp->applicationName()));
    Py_SetProgramName(name);
    Py_Initialize();

    // Export our wrappers to python
    initelapse();
}

/*!
 * Add the parent directory of the given \a dir to python's search path.
 */
void addParentToPythonPath(QDir dir)
{
    dir.cdUp();
    const char *path = qPrintable(dir.absolutePath());

    py::list sys_path = py::extract<py::list>(py::import("sys").attr("path"));
    if (!sys_path.contains(path))
        sys_path.append(path);
}

/*!
 * Load the python module with the given \a moduleName and get the list of
 * elapse::elements classes that it exports.
 * \return a mapping from class names to python class objects.
 */
QMap<QString, py::object> getClasses(const QString &moduleName)
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
