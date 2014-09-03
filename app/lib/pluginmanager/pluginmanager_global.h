#ifndef PLUGINMANAGER_GLOBAL_H
#define PLUGINMANAGER_GLOBAL_H

#include <QtCore>
#include "elapse/datatypes.h"

namespace elapse { namespace plugin {

/*!
 * \brief The HostID enum lists the available plugin::Host%s.
 */
enum class HostID
{
    Static,
    Native,
    Python,
};

/*!
 * \brief The PluginInfo struct contains information to uniquely identify
 * a plugin.
 */
struct PluginInfo
{
    QString name;                    ///< The name of the plugin
    QString path;                    ///< Absolute path to the plugin file
    HostID host;               ///< Which PluginHost can load this plugin
};

/*!
 * \brief The ClassInfo struct contains information to uniquely identify
 * a class within a particular plugin.
 */
struct ClassInfo
{
    QString elementClass;            ///< The element base class this class inherits from
    data::Signal::Type signalType;   ///< The signal type this class works with (if specified)
    QString className;               ///< The name of the class
};

/*!
 * \brief The PluginData struct contains information about all of the classes
 * provided by a plugin.
 */
struct PluginData
{
    PluginInfo plugin;               ///< Info about the plugin
    QList<ClassInfo> classes;        ///< Info about the classes the plugin provides
};

}} // namespace elapse::plugin

#endif // PLUGINMANAGER_GLOBAL_H
