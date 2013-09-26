#ifndef LOGGERCONSUMERPLUGIN_H
#define LOGGERCONSUMERPLUGIN_H

#include "plugin.h"
#include "loggerconsumer.h"

class LoggerPlugin : public DataConsumerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DataConsumerInterface_iid)
    Q_CLASSINFO("description", "DataConsumer that logs to stdout")
protected:
    ClassList classes()
    {
        return { LoggerConsumer::staticMetaObject };
    }
};

#endif // LOGGERCONSUMERPLUGIN_H
