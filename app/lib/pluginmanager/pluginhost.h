#ifndef PLUGINHOST_H
#define PLUGINHOST_H

#include "pluginmanager_global.h"

class PluginHost
{
public:
    virtual ~PluginHost() {}

    struct PluginData
    {
        PluginInfo plugin;
        QList<ClassInfo> classes;
    };

    virtual PluginData getInfo(const QString &pluginPath) = 0;

    virtual QObject *instantiateClass(const PluginInfo &plugin,
                                      const ClassInfo &cls) = 0; // FIXME: shared_ptr
};

#endif // PLUGINHOST_H
