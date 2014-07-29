#ifndef PYTHONPLUGINHOST_H
#define PYTHONPLUGINHOST_H

#include "pluginhost.h"


/*!
 * \brief The PythonPluginHost class loads plugins implemented in Python.
 *
 * The PythonPluginHost internally launches a Python interpreter which is used
 * to load Python packages. A plugin is a Python package containing a list of
 * class objects called `classes`.
 */

class PythonPluginHost : public PluginHost
{
public:
    PythonPluginHost();

protected:
    PluginData getInfo(const QString &pluginPath);
    QObject *instantiateClass(const PluginInfo &plugin, const ClassInfo &cls);
    Deleter deleter();
};

#endif // PYTHONPLUGINHOST_H
