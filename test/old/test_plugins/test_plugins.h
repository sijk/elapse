#ifndef TEST_PLUGINS_H
#define TEST_PLUGINS_H

#include "plugin_base.h"
#include "producer.h"
#include "consumer.h"

typedef PluginInterface<Producer> ProducerInterface;
#define ProducerInterface_iid "org.nzbri.elapse.test.ProducerInterface"
Q_DECLARE_INTERFACE(ProducerInterface, ProducerInterface_iid)

class ProducerPlugin : public QObject, public ProducerInterface
{
    Q_OBJECT
    Q_INTERFACES(ProducerInterface)
};

typedef PluginInterface<Consumer> ConsumerInterface;
#define ConsumerInterface_iid "org.nzbri.elapse.test.ConsumerInterface"
Q_DECLARE_INTERFACE(ConsumerInterface, ConsumerInterface_iid)

class ConsumerPlugin : public QObject, public ConsumerInterface
{
    Q_OBJECT
    Q_INTERFACES(ConsumerInterface)
};

#endif // TEST_PLUGINS_H
