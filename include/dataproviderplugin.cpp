#include "dataproviderplugin.h"
#include <QDebug>

QStringList DataProviderPlugin::keys()
{
    QStringList keys;
    foreach (QMetaObject cls, classes())
        keys << cls.className();
    return keys;
}

DataProvider *DataProviderPlugin::create(const QString &key)
{
    QString lkey = key.toLower();
    foreach (QMetaObject cls, classes()) {
        if (lkey == QString(cls.className()).toLower()) {
            return qobject_cast<DataProvider*>(cls.newInstance());
        }
    }
    return 0;
}
