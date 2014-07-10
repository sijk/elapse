#ifndef PYTHONPLUGINHOST_H
#define PYTHONPLUGINHOST_H

#include "pluginhost.h"

class PythonPluginHost : public PluginHost
{
public:
    PythonPluginHost();
    ~PythonPluginHost();

    PluginData getInfo(const QString &pluginPath);
    QSharedPointer<QObject> instantiateClass(const PluginInfo &plugin,
                                             const ClassInfo &cls);

private:
    struct Private;
    Private *d;
};

#endif // PYTHONPLUGINHOST_H
