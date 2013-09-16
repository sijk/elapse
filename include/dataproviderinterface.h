#ifndef DATAPROVIDERINTERFACE_H
#define DATAPROVIDERINTERFACE_H

#include <QtPlugin>

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

typedef QSharedPointer<DataProvider> DataProviderPtr;


class DataProviderFactory
{
public:
    virtual ~DataProviderFactory() {}
    virtual DataProviderPtr createProvider(QObject *parent = 0) = 0;
};

#define DataProviderFactory_iid "org.nzbri.elapse.DataProviderFactory/1.0"

Q_DECLARE_INTERFACE(DataProviderFactory, DataProviderFactory_iid)


#define DEFAULT_DATA_PROVIDER_FACTORY(Provider)                             \
    class Provider##Factory : public QObject, public DataProviderFactory    \
    {                                                                       \
        Q_OBJECT                                                            \
        Q_PLUGIN_METADATA(IID DataProviderFactory_iid)                      \
        Q_INTERFACES(DataProviderFactory)                                   \
    public:                                                                 \
        DataProviderPtr createProvider(QObject *parent = 0)                 \
        {                                                                   \
            DataProvider *p = new Provider(parent);                         \
            return DataProviderPtr(p);                                      \
        }                                                                   \
    };

#endif // DATAPROVIDERINTERFACE_H
