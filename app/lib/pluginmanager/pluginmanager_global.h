#ifndef PLUGINMANAGER_GLOBAL_H
#define PLUGINMANAGER_GLOBAL_H

#include <QtCore>
#include "elapse/sampletypes.h"

enum PluginHostID
{
    NATIVE,
    PYTHON,
    N_PLUGIN_HOSTS
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

//typedef QMap<const char *, ClassInfo> ElementSetInfo;

#endif // PLUGINMANAGER_GLOBAL_H
