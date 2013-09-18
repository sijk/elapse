#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>

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

#define DataProviderInterface_iid "org.nzbri.elapse.DataProviderInterface"

#endif // DATAPROVIDER_H
