#ifndef PLUGINMANAGER_DEF_H
#define PLUGINMANAGER_DEF_H

#include <QtCore>

/*!
 * \brief The PluginItemDataRole enum enumerates the special data roles used in
 * the PluginManager's internal data model.
 */

enum PluginItemDataRole
{
    SIGNALTYPE_ROLE = Qt::UserRole,
    FILEPATH_ROLE
};

#endif // PLUGINMANAGER_DEF_H
