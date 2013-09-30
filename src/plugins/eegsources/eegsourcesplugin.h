#ifndef EEGSOURCESPLUGIN_H
#define EEGSOURCESPLUGIN_H

#include "plugin.h"
#include "udpeegdatasource.h"
#include "tcpclienteegdatasource.h"
#include "threadedtcpclienteegdatasource.h"
#include "dummyeegsource.h"

class EegSourcesPlugin : public DataSourcePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DataSourceInterface_iid)
protected:
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
