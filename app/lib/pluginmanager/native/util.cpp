#include <QPluginLoader>
#include <QStaticPlugin>
#include "elapse/plugin.h"
#include "pluginmanager_global.h"
#include "util.h"

static const QMetaObject *baseClass(const QMetaObject *obj)
{
    const QMetaObject *super = obj->superClass();
    if (super && super != &QObject::staticMetaObject)
        return baseClass(super);
    return obj;
}

static QString stripNamespace(const char *ident)
{
    QString s(ident);
    return s.remove(0, s.lastIndexOf(':') + 1);
}

static elapse::data::Signal::Type signalType(const QMetaObject &obj)
{
    int typeIdx = obj.indexOfClassInfo("SignalType");
    if (typeIdx >= 0) {
        const char *type = obj.classInfo(typeIdx).value();
        return elapse::data::Signal::fromString(type);
    }
    return elapse::data::Signal::INVALID;
}

template<class T>
bool getPluginDataFrom(T &plugin, PluginData &data)
{
    data.plugin.name = plugin.metaData()["className"].toString();

    QObject *pluginInstance = plugin.instance();
    auto factory = qobject_cast<elapse::PluginInterface*>(pluginInstance);
    if (!factory)
        return false;

    for (const QMetaObject &obj : factory->classes()) {
        ClassInfo cls;
        cls.elementClass = stripNamespace(baseClass(&obj)->className());
        cls.signalType = signalType(obj);
        cls.className = obj.className();
        data.classes.append(cls);
    }

    return true;
}

// Explicitly instantiate template with relevant Qt plugin types
template bool getPluginDataFrom(const QStaticPlugin &plugin, PluginData &data);
template bool getPluginDataFrom(QPluginLoader &plugin, PluginData &data);

QObject *instantiateClassFrom(QObject *pluginInstance, const QString &className)
{
    auto factory = qobject_cast<elapse::PluginInterface*>(pluginInstance);
    if (!factory)
        return nullptr;

    for (const QMetaObject &obj : factory->classes()) {
        if (obj.className() == className) {
            QObject *object = obj.newInstance();
            if (object)
                return object;
        }
    }

    return nullptr;
}
