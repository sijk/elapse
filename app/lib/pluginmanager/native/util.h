#ifndef NATIVE_UTIL_H
#define NATIVE_UTIL_H

class QObject;
class QString;

namespace elapse { namespace plugin {

class PluginData;

/*!
 * \brief Helper functions for working with plugins implemented in C++.
 */
namespace native {

/*!
 * Inspect the given \a plugin and extract its plugin \a data. The \a plugin
 * may be an instance of either QStaticPlugin or QPluginLoader.
 * \return false if the \a plugin could not be inspected, otherwise true.
 */
template<class T> bool getPluginDataFrom(T &plugin, PluginData &data);

/*!
 * Create an instance of the class \a className from the given
 * \a pluginInstance.
 * \return the instance, or null on failure.
 */
QObject *instantiateClassFrom(QObject *pluginInstance, const QString &className);

}}} // namespace elapse::plugin::native

#endif // NATIVE_UTIL_H
