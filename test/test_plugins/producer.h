#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include "plugin.h"

class Producer : public QObject
{
    Q_OBJECT
public:
    Producer(QObject *parent = 0) : QObject(parent) {}

signals:
    void dataReady(double data);

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
};


#define ProducerInterface_iid "org.nzbri.elapse.test.ProducerInterface"

typedef FactoryInterface<Producer> ProducerInterface;
Q_DECLARE_INTERFACE(ProducerInterface, ProducerInterface_iid)

class ProducerPlugin : public QObject, public BasePlugin<Producer>
{
    Q_OBJECT
    Q_INTERFACES(ProducerInterface)
};

#endif // DATAPROVIDER_H
