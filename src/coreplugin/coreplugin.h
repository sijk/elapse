#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include "plugin.h"
#include "tcpclientdatasource.h"
#include "dummyeegsource.h"
#include "eegdecoder.h"

class CorePlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
public:
    ClassList classes()
    {
        return {
            TcpClientDataSource::staticMetaObject,
            DummyEegSource::staticMetaObject,
            EegDecoder::staticMetaObject
        };
    }
};

#endif // COREPLUGIN_H
