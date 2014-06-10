#include <QApplication>
#include <boost/python.hpp>
#include "pythonpluginhost.h"

namespace py = boost::python;


struct PythonPluginHost::Private
{
    py::object main_module;
    py::object main_ns;
};


PythonPluginHost::PythonPluginHost() :
    d(new Private)
{
    char *name = const_cast<char*>(qPrintable(qApp->applicationName()));
    Py_SetProgramName(name);
    Py_Initialize();

    d->main_module = py::import("__main__");
    d->main_ns = d->main_module.attr("__dict__");
}

PythonPluginHost::~PythonPluginHost()
{
    delete d;
}

PluginHost::PluginData PythonPluginHost::getInfo(const QString &pluginPath)
{
    Q_UNUSED(pluginPath)
    PluginData data;
    return data;
}

QObject *PythonPluginHost::instantiateClass(const PluginInfo &plugin, const ClassInfo &cls)
{
    Q_UNUSED(plugin)
    Q_UNUSED(cls)
    return nullptr;
}
