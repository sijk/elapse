#ifndef QENUMUTILS_H
#define QENUMUTILS_H

#include <QMetaObject>
#include <QMetaEnum>

/*!
 * Given an enum called \a enumName declared inside class \a T with the
 * \c Q_ENUMS macro, return the key corresponding to the given \a value.
 */
template<class T>
const char *enumToString(const char *enumName, int value)
{
    QMetaObject mobj = T::staticMetaObject;
    QMetaEnum menum = mobj.enumerator(mobj.indexOfEnumerator(enumName));
    return menum.valueToKey(value);
}

/*!
 * Given an enum called \a enumName declared inside class \a T with the
 * \c Q_ENUMS macro, return the value corresponding to the given \a key.
 */
template<class T>
int stringToEnum(const char *enumName, const QString &key)
{
    QMetaObject mobj = T::staticMetaObject;
    QMetaEnum menum = mobj.enumerator(mobj.indexOfEnumerator(enumName));
    return menum.keyToValue(key.toLatin1().constData());
}

#endif // QENUMUTILS_H
