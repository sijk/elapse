#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>
#include <QStringList>


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<class T>
class FactoryInterface
{
public:
    virtual ~FactoryInterface() {}

    virtual QStringList keys() = 0;
    virtual T *create(const QString &key) = 0;
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<class T>
class BasePlugin : public FactoryInterface<T>
{
public:
    virtual ~BasePlugin() {}

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

#endif // PLUGIN_H
