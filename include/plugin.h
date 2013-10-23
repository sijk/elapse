#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>


class PluginInterface
{
public:
    typedef QList<QMetaObject> ClassList;
    virtual ClassList classes() = 0;
};

#define PluginInterface_iid "org.nzbri.elapse.PluginInterface"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)


class Plugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
};


#endif // PLUGIN_H
