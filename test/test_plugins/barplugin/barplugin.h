#ifndef BARPLUGIN_H
#define BARPLUGIN_H

#include <elapse/plugin.h>
#include "bareegdecoder.h"
#include "barvideodecoder.h"


class BarPlugin : public QObject, public elapse::PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid)
    Q_INTERFACES(elapse::PluginInterface)
    ELAPSE_EXPORT_CLASSES(
        BarEegDecoder,
        BarVideoDecoder
    )
};

#endif // BARPLUGIN_H

