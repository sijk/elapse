#ifndef NATIVEPLUGINHOST_H
#define NATIVEPLUGINHOST_H

#include "pluginhost.h"

namespace elapse { namespace plugin {

/*!
 * \brief The NativeHost class loads \ref elapse::plugin::Interface "plugins"
 * implemented in C++.
 *
 * \ingroup plugins-int
 */

class NativeHost : public Host
{
protected:
    PluginData getInfo(const QString &pluginPath);
    QObject *instantiateClass(const PluginInfo &pluginInfo,
                              const ClassInfo &classInfo);
};

}} // namespace elapse::plugin

#endif // NATIVEPLUGINHOST_H
