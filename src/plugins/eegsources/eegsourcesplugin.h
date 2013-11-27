#ifndef EEGSOURCESPLUGIN_H
#define EEGSOURCESPLUGIN_H

#include "plugin.h"
#include "udpeegdatasource.h"
#include "tcpclienteegdatasource.h"
#include "threadedtcpclienteegdatasource.h"
#include "dummyeegsource.h"

class EegSourcesPlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
public:
    ClassList classes()
    {
        return {
            UdpEegDataSource::staticMetaObject,
            TcpClientEegDataSource::staticMetaObject,
            ThreadedTcpClientEegDataSource::staticMetaObject,
            DummyEegSource::staticMetaObject
        };
    }
};

#endif // EEGSOURCESPLUGIN_H
