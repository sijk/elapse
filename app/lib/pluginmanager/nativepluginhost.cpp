#include <QPluginLoader>
#include <QxtLogger>
#include "elapse/plugin.h"
#include "nativepluginhost.h"


namespace {

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

} // namespace


PluginHost::PluginData NativePluginHost::getInfo(const QString &pluginPath)
{
    PluginData data;

    QPluginLoader loader(pluginPath);
    QObject *plugin = loader.instance();
    auto factory = qobject_cast<elapse::PluginInterface*>(plugin);

    if (!factory) {
        qxtLog->debug(loader.errorString());
        return data;
    }

    data.plugin.host = NATIVE;
    data.plugin.path = pluginPath;
    data.plugin.name = loader.metaData()["className"].toString();

    for (const QMetaObject &obj : factory->classes()) {
        ClassInfo cls;
        cls.elementClass = stripNamespace(baseClass(&obj)->className());
        cls.signalType = signalType(obj);
        cls.className = obj.className();
        data.classes.append(cls);
    }

    return data;
}

QSharedPointer<QObject> NativePluginHost::instantiateClass(const PluginInfo &pluginInfo,
                                                           const ClassInfo &classInfo)
{
    QSharedPointer<QObject> instance;

    QPluginLoader loader(pluginInfo.path);
    QObject *plugin = loader.instance();
    auto factory = qobject_cast<elapse::PluginInterface*>(plugin);

    if (!factory) {
        qxtLog->debug(loader.errorString());
        return instance;
    }

    for (const QMetaObject &obj : factory->classes()) {
        if (obj.className() == classInfo.className) {
            instance.reset(obj.newInstance());
            if (instance)
                break;
        }
    }

    return instance;
}
