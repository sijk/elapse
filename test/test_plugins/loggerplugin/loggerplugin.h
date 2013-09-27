#ifndef LOGGERCONSUMERPLUGIN_H
#define LOGGERCONSUMERPLUGIN_H

#include "plugin.h"
#include "loggerconsumer.h"

class LoggerPlugin : public ConsumerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ConsumerInterface_iid)
    Q_CLASSINFO("description", "Consumer that logs to stdout")
protected:
    ClassList classes()
    {
        return { LoggerConsumer::staticMetaObject };
    }
};

#endif // LOGGERCONSUMERPLUGIN_H
