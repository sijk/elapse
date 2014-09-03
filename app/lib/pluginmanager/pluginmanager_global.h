#ifndef PLUGINMANAGER_GLOBAL_H
#define PLUGINMANAGER_GLOBAL_H

#include <QtCore>
#include "elapse/datatypes.h"

/*!
 * \brief The PluginHostID enum lists the available PluginHost%s.
 */
enum class PluginHostID
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
    PluginHostID host;               ///< Which PluginHost can load this plugin
};

/*!
 * \brief The ClassInfo struct contains information to uniquely identify
 * a class within a particular plugin.
 */
struct ClassInfo
{
    QString elementClass;            ///< The element base class this class inherits from
    elapse::data::Signal::Type signalType; ///< The signal type this class works with (if specified)
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

#endif // PLUGINMANAGER_GLOBAL_H
