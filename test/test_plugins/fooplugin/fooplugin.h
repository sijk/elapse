#ifndef FOOPLUGIN_H
#define FOOPLUGIN_H

#include "plugin.h"
#include "fooeegdecoder.h"
#include "foodummysource.h"


class FooPlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
public:
    ClassList classes()
    {
        return {
            FooEegDecoder::staticMetaObject,
            FooDummySource::staticMetaObject
        };
    }
};

#endif // FOOPLUGIN_H

