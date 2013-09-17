#ifndef DATAPROVIDERPLUGIN_H
#define DATAPROVIDERPLUGIN_H

#include <QtPlugin>
#include <QStringList>
#include "dataprovider.h"

class DataProviderFactoryInterface
{
public:
    virtual QStringList keys() = 0;
    virtual DataProvider *create(const QString &key) = 0;
};

#define DataProviderFactoryInterface_iid "org.nzbri.elapse.DataProviderFactoryInterface/1.0"
Q_DECLARE_INTERFACE(DataProviderFactoryInterface, DataProviderFactoryInterface_iid)


class DataProviderPlugin : public QObject, public DataProviderFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(DataProviderFactoryInterface)

public:
    QStringList keys();
    DataProvider *create(const QString &key);

protected:
    typedef QList<QMetaObject> ClassList;
    virtual ClassList classes() = 0;
};

#endif // DATAPROVIDERPLUGIN_H
