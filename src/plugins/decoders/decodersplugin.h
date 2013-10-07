#ifndef DECODERSPLUGIN_H
#define DECODERSPLUGIN_H

#include "plugin.h"
#include "eegdecoder.h"

class DecodersPlugin : public SampleDecoderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SampleDecoderInterface_iid)
protected:
    ClassList classes()
    {
        return {
            EegDecoder::staticMetaObject
        };
    }
};

#endif // DECODERSPLUGIN_H
