#ifndef COSINEPLUGIN_H
#define COSINEPLUGIN_H

#include "plugin.h"
#include "cosineproducer.h"

class CosinePlugin : public ProducerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ProducerInterface_iid)
    Q_CLASSINFO("description", "Producers that provide cosine waves")
protected:
    ClassList classes()
    {
        return { CosineProducer::staticMetaObject };
    }
};

#endif // COSINEPLUGIN_H
