#ifndef TCPPROVIDERPLUGIN_H
#define TCPPROVIDERPLUGIN_H

#include "plugin.h"
#include "tcpprovider.h"
#include "sineprovider.h"

class SinePlugin : public DataProviderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DataProviderInterface_iid)
    Q_CLASSINFO("description", "DataProviders that provide sine waves")
protected:
    ClassList classes()
    {
        return {
            SineProvider::staticMetaObject,
            TcpProvider::staticMetaObject
        };
    }
};

#endif // TCPPROVIDERPLUGIN_H
