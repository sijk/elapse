#ifndef NATIVEPLUGINHOST_H
#define NATIVEPLUGINHOST_H

#include "pluginhost.h"

class NativePluginHost : public PluginHost
{
public:
    PluginData getInfo(const QString &pluginPath);
    QObject *instantiateClass(const PluginInfo &pluginInfo,
                              const ClassInfo &classInfo);
};

#endif // NATIVEPLUGINHOST_H
