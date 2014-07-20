#ifndef PLUGINMANAGER_GLOBAL_H
#define PLUGINMANAGER_GLOBAL_H

#include <QtCore>
#include "elapse/sampletypes.h"

enum class PluginHostID
{
    Native,
    Python,
};

struct PluginInfo
{
    QString name;
    QString path;
    PluginHostID host;
};

struct ClassInfo
{
    QString elementClass;
    elapse::Signal::Type signalType;
    QString className;
};

struct PluginData
{
    PluginInfo plugin;
    QList<ClassInfo> classes;
};

#endif // PLUGINMANAGER_GLOBAL_H
