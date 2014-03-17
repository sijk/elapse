#ifndef BARPLUGIN_H
#define BARPLUGIN_H

#include <elapse/plugin.h>
#include "bareegdecoder.h"
#include "barvideodecoder.h"


class BarPlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
public:
    ClassList classes()
    {
        return {
            BarEegDecoder::staticMetaObject,
            BarVideoDecoder::staticMetaObject
        };
    }
};

#endif // BARPLUGIN_H

