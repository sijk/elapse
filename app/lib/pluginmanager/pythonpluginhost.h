#ifndef PYTHONPLUGINHOST_H
#define PYTHONPLUGINHOST_H

#include "pluginhost.h"

class PythonPluginHost : public PluginHost
{
public:
    PythonPluginHost();
    PluginData getInfo(const QString &pluginPath);

protected:
    QObject *instantiateClass(const PluginInfo &plugin, const ClassInfo &cls);
    Deleter deleter();
};

#endif // PYTHONPLUGINHOST_H
