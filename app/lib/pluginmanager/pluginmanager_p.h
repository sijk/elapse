#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

#include "pluginmanager.h"
#include "pluginmanager_global.h"
#include "pluginhost.h"

class PluginManagerPrivate
{
public:
    PluginManagerPrivate(PluginManager *q);
    ~PluginManagerPrivate();

    static PluginManagerPrivate *expose(PluginManager *manager);

    QDir searchPath;
    PluginHost *hosts[N_PLUGIN_HOSTS];

private:
    PluginManager * const q_ptr;
    Q_DECLARE_PUBLIC(PluginManager)
};

#endif // PLUGINMANAGER_P_H
