#ifndef BARPLUGIN_H
#define BARPLUGIN_H

#include "plugin.h"
#include "bareegdecoder.h"


class BarPlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
public:
    ClassList classes()
    {
        return {
            BarEegDecoder::staticMetaObject
        };
    }
};

#endif // BARPLUGIN_H

