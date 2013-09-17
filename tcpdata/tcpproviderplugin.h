#ifndef TCPPROVIDERPLUGIN_H
#define TCPPROVIDERPLUGIN_H

#include "dataproviderplugin.h"
#include "tcpprovider.h"

class TcpProviderPlugin : public DataProviderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DataProviderFactoryInterface_iid)
protected:
    ClassList classes() { return { TcpProvider::staticMetaObject }; }
};

#endif // TCPPROVIDERPLUGIN_H
