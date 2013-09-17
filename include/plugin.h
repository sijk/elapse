#ifndef DATAPROVIDERPLUGIN_H
#define DATAPROVIDERPLUGIN_H

#include <QtPlugin>
#include <QStringList>
#include "dataprovider.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<class T>
class FactoryInterface
{
public:
    virtual QStringList keys() = 0;
    virtual T *create(const QString &key) = 0;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<class T>
class BasePlugin : public FactoryInterface<T>
{
public:
    QStringList keys();
    T *create(const QString &key);

protected:
    typedef QList<QMetaObject> ClassList;
    virtual ClassList classes() = 0;
};

template<class T>
QStringList BasePlugin<T>::keys()
{
    QStringList keys;
    foreach (QMetaObject cls, classes())
        keys << cls.className();
    return keys;
}

template<class T>
T *BasePlugin<T>::create(const QString &key)
{
    QString lkey = key.toLower();
    foreach (QMetaObject cls, classes()) {
        if (lkey == QString(cls.className()).toLower()) {
            return qobject_cast<T*>(cls.newInstance());
        }
    }
    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

typedef FactoryInterface<DataProvider> DataProviderInterface;
#define DataProviderInterface_iid "org.nzbri.elapse.DataProviderInterface/1.0"
Q_DECLARE_INTERFACE(DataProviderInterface, DataProviderInterface_iid)

class DataProviderPlugin : public QObject, public BasePlugin<DataProvider>
{
    Q_OBJECT
    Q_INTERFACES(DataProviderInterface)
};

#endif // DATAPROVIDERPLUGIN_H
