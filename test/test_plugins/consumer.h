#ifndef DATACONSUMER_H
#define DATACONSUMER_H

#include <QObject>
#include "plugin.h"

class Consumer : public QObject
{
    Q_OBJECT
public:
    Consumer(QObject *parent = 0) : QObject(parent) {}

public slots:
    virtual void onData(double data) = 0;
};


#define ConsumerInterface_iid "org.nzbri.elapse.test.ConsumerInterface"

typedef FactoryInterface<Consumer> ConsumerInterface;
Q_DECLARE_INTERFACE(ConsumerInterface, ConsumerInterface_iid)

class ConsumerPlugin : public QObject, public BasePlugin<Consumer>
{
    Q_OBJECT
    Q_INTERFACES(ConsumerInterface)
};

#endif // DATACONSUMER_H
