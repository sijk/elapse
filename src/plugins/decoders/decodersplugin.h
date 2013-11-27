#ifndef DECODERSPLUGIN_H
#define DECODERSPLUGIN_H

#include "plugin.h"
#include "eegdecoder.h"

class DecodersPlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
public:
    ClassList classes()
    {
        return {
            EegDecoder::staticMetaObject
        };
    }
};

#endif // DECODERSPLUGIN_H
