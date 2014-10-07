#include <QDir>
#include <boost/python.hpp>
#include "pythonpluginhost.h"
#include "python/host.h"
#include "python/exception.h"

namespace elapse { namespace plugin {

/*!
 * Create a new PythonPluginHost and initialize the Python interpreter.
 */
PythonHost::PythonHost()
{
    python::initPython();
}

/*!
 * Import the Python package at \a pluginPath and extract the list of classes.
 */
PluginData PythonHost::getInfo(const QString &pluginPath)
{
    PluginData data;
    QDir dir(pluginPath);
    QString moduleName(dir.dirName());

    if (!dir.exists("__init__.py"))
        return data;

    try {
        data.plugin.host = HostID::Python;
        data.plugin.path = pluginPath;
        data.plugin.name = moduleName;

        python::addParentToPythonPath(dir);
        auto classes = python::getClasses(moduleName);

        for (auto i = classes.cbegin(); i != classes.cend(); i++) {
            ClassInfo cls;
            cls.elementClass = python::baseClassName(i.value());
            cls.signalType = python::signalType(i.value());
            cls.className = i.key();
            data.classes.append(cls);
        }
    } catch (const boost::python::error_already_set &) {
        python::logException();
        return PluginData();
    }

    return data;
}

QObject *PythonHost::instantiateClass(const PluginInfo &plugin,
                                      const ClassInfo &cls)
{
    QObject *obj;
    QDir dir(plugin.path);

    try {
        auto classes = python::getClasses(dir.dirName());
        boost::python::object pyobj = classes[cls.className]();
        obj = python::extractQObject(pyobj, cls.elementClass);
        python::storeInstance(obj, pyobj);
    } catch (const boost::python::error_already_set&) {
        python::logException();
        return nullptr;
    }

    return obj;
}

/*!
 * \return an elements::ElementDeleter that will remove objects from the
 * internal cache of Python instances.
 */
elements::ElementDeleter PythonHost::deleter()
{
    return &python::removeInstance;
}

}} // namespace elapse::plugin
