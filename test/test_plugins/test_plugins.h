#ifndef TEST_PLUGINS_H
#define TEST_PLUGINS_H

#include "plugin_base.h"
#include "producer.h"
#include "consumer.h"

typedef FactoryInterface<Producer> ProducerInterface;
Q_DECLARE_INTERFACE(ProducerInterface, ProducerInterface_iid)

class ProducerPlugin : public QObject, public BasePlugin<Producer>
{
    Q_OBJECT
    Q_INTERFACES(ProducerInterface)
};

typedef FactoryInterface<Consumer> ConsumerInterface;
Q_DECLARE_INTERFACE(ConsumerInterface, ConsumerInterface_iid)

class ConsumerPlugin : public QObject, public BasePlugin<Consumer>
{
    Q_OBJECT
    Q_INTERFACES(ConsumerInterface)
};

#endif // TEST_PLUGINS_H
