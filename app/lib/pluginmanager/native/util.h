#ifndef NATIVE_UTIL_H
#define NATIVE_UTIL_H

#include <QMetaObject>
#include "elapse/sampletypes.h"


const QMetaObject *baseClass(const QMetaObject *obj);

QString stripNamespace(const char *ident);

elapse::Signal::Type signalType(const QMetaObject &obj);

#endif // NATIVE_UTIL_H
