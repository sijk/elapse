#ifndef STATICPLUGINHOST_H
#define STATICPLUGINHOST_H

#include "pluginhost.h"


/*!
 * \brief The StaticPluginHost class loads the static \ref core-plugin.
 *
 * \ingroup plugins-int
 */

class StaticPluginHost : public PluginHost
{
public:
    QList<PluginData> searchForPluginsIn(QDir &dir);

protected:
    PluginData getInfo(const QString &pluginPath);
    QObject *instantiateClass(const PluginInfo &pluginInfo,
                              const ClassInfo &classInfo);
};

#endif // STATICPLUGINHOST_H
