#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtPlugin>
#include <QStringList>

template<class T>
class PluginInterface
{
public:
    typedef QList<QMetaObject> ClassList;
    virtual ClassList classes() = 0;
};

#endif // PLUGINBASE_H
