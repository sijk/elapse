#ifndef FOOPLUGIN_H
#define FOOPLUGIN_H

#include <elapse/plugin.h>
#include "fooeegdecoder.h"
#include "foodummysource.h"


class FooPlugin : public elapse::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid)
    ELAPSE_EXPORT_CLASSES(
        FooEegDecoder,
        FooDummySource
    )
};

#endif // FOOPLUGIN_H

