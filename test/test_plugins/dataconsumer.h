#ifndef DATACONSUMER_H
#define DATACONSUMER_H

#include <QObject>
#include "plugin.h"

class DataConsumer : public QObject
{
    Q_OBJECT
public:
    DataConsumer(QObject *parent = 0) : QObject(parent) {}

public slots:
    virtual void onData(double data) = 0;
};


#define DataConsumerInterface_iid "org.nzbri.elapse.test.DataConsumerInterface"

typedef FactoryInterface<DataConsumer> DataConsumerInterface;
Q_DECLARE_INTERFACE(DataConsumerInterface, DataConsumerInterface_iid)

class DataConsumerPlugin : public QObject, public BasePlugin<DataConsumer>
{
    Q_OBJECT
    Q_INTERFACES(DataConsumerInterface)
};

#endif // DATACONSUMER_H
