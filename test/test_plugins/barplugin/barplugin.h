#ifndef BARPLUGIN_H
#define BARPLUGIN_H

#include <elapse/plugin.h>
#include "bareegdecoder.h"
#include "barvideodecoder.h"


class BarPlugin : public elapse::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid)
public:
    ClassList classes()
    {
        return ELAPSE_CLASSLIST(BarEegDecoder, BarVideoDecoder);
    }
};

#endif // BARPLUGIN_H

