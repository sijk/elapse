#include "util.h"

const QMetaObject *baseClass(const QMetaObject *obj)
{
    const QMetaObject *super = obj->superClass();
    if (super && super != &QObject::staticMetaObject)
        return baseClass(super);
    return obj;
}

QString stripNamespace(const char *ident)
{
    QString s(ident);
    return s.remove(0, s.lastIndexOf(':') + 1);
}

elapse::Signal::Type signalType(const QMetaObject &obj)
{
    int typeIdx = obj.indexOfClassInfo("SignalType");
    if (typeIdx >= 0) {
        const char *type = obj.classInfo(typeIdx).value();
        return elapse::Signal::fromString(type);
    }
    return elapse::Signal::INVALID;
}
