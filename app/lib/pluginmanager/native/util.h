#ifndef NATIVE_UTIL_H
#define NATIVE_UTIL_H

class QObject;
class QString;
class PluginData;

// T == QStaticPlugin || QPluginloader
template<class T> bool getPluginDataFrom(T &plugin, PluginData &data);

QObject *instantiateClassFrom(QObject *pluginInstance, const QString &className);

#endif // NATIVE_UTIL_H
