#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "nativepluginhost.h"


PluginManagerPrivate::PluginManagerPrivate(PluginManager *q) :
    q_ptr(q)
{
    hosts[NATIVE] = new NativePluginHost;
}

PluginManagerPrivate::~PluginManagerPrivate()
{
    for (uint i = 0; i < N_PLUGIN_HOSTS; i++)
        delete hosts[i];
}

PluginManagerPrivate *PluginManagerPrivate::expose(PluginManager *manager)
{
    return manager->d_func();
}


PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    d_ptr(new PluginManagerPrivate(this))
{
}

PluginManager::~PluginManager()
{
    delete d_ptr;
}

QDir PluginManager::searchPath() const
{
    Q_D(const PluginManager);
    return d->searchPath;
}

void PluginManager::setSearchPath(QDir newPath)
{
    Q_D(PluginManager);
    d->searchPath = newPath;
}

void PluginManager::selectPluginsToLoad()
{
    show();
}

void PluginManager::loadPluginsFromSettings()
{

}

void PluginManager::loadPluginsFromSelection()
{

}
