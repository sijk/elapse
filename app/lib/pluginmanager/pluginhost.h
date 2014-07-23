#ifndef PLUGINHOST_H
#define PLUGINHOST_H

#include "pluginmanager_global.h"

class PluginHost
{
public:
    virtual ~PluginHost() {}

    virtual PluginData getInfo(const QString &pluginPath) = 0;

    template<class T> QSharedPointer<T>
    instantiate(const PluginInfo &plugin, const ClassInfo &cls)
    {
        QObject *instance = instantiateClass(plugin, cls);
        return QSharedPointer<T>(qobject_cast<T*>(instance), deleter());
    }

protected:
    virtual QObject*
    instantiateClass(const PluginInfo &plugin, const ClassInfo &cls) = 0;

    typedef std::function<void(QObject*)> Deleter;
    virtual Deleter deleter() { return &QObject::deleteLater; }
};

#endif // PLUGINHOST_H
