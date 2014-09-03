#ifndef PLUGINHOST_H
#define PLUGINHOST_H

#include "pluginmanager_global.h"

namespace elapse { namespace plugin {

/*!
 * \brief The plugin::Host class is an abstract factory for loading elements
 * from plugins.
 *
 * This design allows plugins to be written in multiple languages. To add
 * support for a new language, implement a plugin::Host that can load plugins
 * written in that language and implement any required bindings for the
 * \ref pipeline-elements "element base classes".
 *
 * \ingroup plugins-int
 */

class Host
{
public:
    /*!
     * Destroy this PluginHost.
     */
    virtual ~Host() {}

    /*!
     * Search for plugins in the given \a dir. The default implementation calls
     * getInfo() with every readable file and directory in \a dir.
     */
    virtual QList<PluginData> searchForPluginsIn(QDir &dir);

    /*!
     * \return an instance of class \a cls from the given \a plugin.
     * The instance is wrapped in a QSharedPointer with a custom deleter().
     */
    template<class T> QSharedPointer<T>
    instantiate(const PluginInfo &plugin, const ClassInfo &cls)
    {
        QObject *instance = instantiateClass(plugin, cls);
        return QSharedPointer<T>(qobject_cast<T*>(instance), deleter());
    }

protected:
    /*!
     * Analyse the plugin at \a pluginPath and return a PluginData instance
     * describing it. If the file/directory at \a pluginPath is not a plugin
     * that this PluginHost understands, return a default-constructed
     * PluginData instance.
     */
    virtual PluginData getInfo(const QString &pluginPath) = 0;

    /*!
     * Load the given \a plugin and create an instance of the given \a cls.
     */
    virtual QObject*
    instantiateClass(const PluginInfo &plugin, const ClassInfo &cls) = 0;

    /*!
     * A custom deleter function for objects instantiated by this Host.
     */
    typedef std::function<void(QObject*)> Deleter;

    /*!
     * \return a custom deleter function for the instantiated objects.
     * Defaults to \c QObject::deleteLater.
     */
    virtual Deleter deleter() { return &QObject::deleteLater; }
};

}} // namespace elapse::plugin

#endif // PLUGINHOST_H
