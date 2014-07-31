#include <QDir>
#include <QxtLogger>
#include <boost/python.hpp>
#include "pythonpluginhost.h"
#include "python/host.h"


/*!
 * Create a new PythonPluginHost and initialize the Python interpreter.
 */
PythonPluginHost::PythonPluginHost()
{
    pyhost::initPython();
}

/*!
 * Import the Python package at \a pluginPath and extract the list of classes.
 */
PluginData PythonPluginHost::getInfo(const QString &pluginPath)
{
    PluginData data;
    QDir dir(pluginPath);
    QString moduleName(dir.dirName());

    if (!dir.exists("__init__.py"))
        return data;

    try {
        data.plugin.host = PluginHostID::Python;
        data.plugin.path = pluginPath;
        data.plugin.name = moduleName;

        pyhost::addParentToPythonPath(dir);
        auto classes = pyhost::getClasses(moduleName);

        for (auto i = classes.cbegin(); i != classes.cend(); i++) {
            ClassInfo cls;
            cls.elementClass = pyhost::baseClassName(i.value());
            cls.signalType = pyhost::signalType(i.value());
            cls.className = i.key();
            data.classes.append(cls);
        }
    } catch (const boost::python::error_already_set &) {
        PyErr_Print();
        return PluginData();
    }

    return data;
}

QObject *PythonPluginHost::instantiateClass(const PluginInfo &plugin,
                                            const ClassInfo &cls)
{
    QObject *obj;
    QDir dir(plugin.path);

    try {
        auto classes = pyhost::getClasses(dir.dirName());
        boost::python::object pyobj = classes[cls.className]();
        obj = pyhost::extractQObject(pyobj, cls.elementClass);
        pyhost::instances[obj] = pyobj;
    } catch (const boost::python::error_already_set&) {
        PyErr_Print();
        return nullptr;
    }

    return obj;
}

/*!
 * \return a Deleter that will remove objects from the internal cache of
 * Python instances.
 */
PluginHost::Deleter PythonPluginHost::deleter()
{
    return &pyhost::removeInstance;
}
