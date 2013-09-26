#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include "plugin.h"

class DataProvider : public QObject
{
    Q_OBJECT
public:
    DataProvider(QObject *parent = 0) : QObject(parent) {}

signals:
    void dataReady(double data);

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
};


#define DataProviderInterface_iid "org.nzbri.elapse.test.DataProviderInterface"

typedef FactoryInterface<DataProvider> DataProviderInterface;
Q_DECLARE_INTERFACE(DataProviderInterface, DataProviderInterface_iid)

class DataProviderPlugin : public QObject, public BasePlugin<DataProvider>
{
    Q_OBJECT
    Q_INTERFACES(DataProviderInterface)
};

#endif // DATAPROVIDER_H
