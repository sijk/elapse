#ifndef SINEPLUGIN_H
#define SINEPLUGIN_H

#include "test_plugins.h"
#include "tcpproducer.h"
#include "sineproducer.h"

class SinePlugin : public ProducerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ProducerInterface_iid)
    Q_CLASSINFO("description", "Producers that provide sine waves")
protected:
    ClassList classes()
    {
        return {
            SineProducer::staticMetaObject,
            TcpProducer::staticMetaObject
        };
    }
};

#endif // SINEPLUGIN_H