#ifndef MYPLUGIN_H
#define MYPLUGIN_H

//! [include plugin]
#include <elapse/plugin.h>
//! [include plugin] [include elements]
#include "eegpower.h"
#include "simpleclassifier.h"
//! [include elements]

//! [class def]
class MyPlugin : public QObject, public elapse::plugin::Interface
{
//! [class def] [metadata]
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid)
    Q_INTERFACES(elapse::plugin::Interface)
//! [metadata] [export]
    ELAPSE_EXPORT_CLASSES(
        EegPower,
        SimpleClassifier
    )
};
//! [export]

#endif // MYPLUGIN_H

