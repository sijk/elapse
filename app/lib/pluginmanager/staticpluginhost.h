#ifndef STATICPLUGINHOST_H
#define STATICPLUGINHOST_H

#include "pluginhost.h"

namespace elapse { namespace plugin {

/*!
 * \brief The StaticHost class loads the static \ref core-plugin.
 *
 * \ingroup plugins-int
 */

class StaticHost : public Host
{
public:
    QList<PluginData> searchForPluginsIn(QDir &dir);

protected:
    PluginData getInfo(const QString &pluginPath);
    QObject *instantiateClass(const PluginInfo &pluginInfo,
                              const ClassInfo &classInfo);
};

}} // namespace elapse::plugin

#endif // STATICPLUGINHOST_H
