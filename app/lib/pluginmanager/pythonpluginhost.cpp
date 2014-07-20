#include <QDir>
#include <QxtLogger>
#include <boost/python.hpp>
#include "pythonpluginhost.h"
#include "python/util.h"


PythonPluginHost::PythonPluginHost()
{
    pyhost::initPython();
}

PluginData PythonPluginHost::getInfo(const QString &pluginPath)
{
    PluginData data;
    QDir dir(pluginPath);
    QString moduleName(dir.dirName());

    if (!dir.exists("__init__.py"))
        return data;

    try {
        data.plugin.host = PYTHON;
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

QSharedPointer<QObject> PythonPluginHost::instantiateClass(const PluginInfo &plugin,
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
        return QSharedPointer<QObject>();
    }

    return QSharedPointer<QObject>(obj, &pyhost::removeInstance);
}
