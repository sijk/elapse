#ifndef NATIVEPLUGINHOST_H
#define NATIVEPLUGINHOST_H

#include "pluginhost.h"


/*!
 * \brief The NativePluginHost class loads plugins implemented in C++.
 */

class NativePluginHost : public PluginHost
{
protected:
    PluginData getInfo(const QString &pluginPath);
    QObject *instantiateClass(const PluginInfo &pluginInfo,
                              const ClassInfo &classInfo);
};

#endif // NATIVEPLUGINHOST_H
