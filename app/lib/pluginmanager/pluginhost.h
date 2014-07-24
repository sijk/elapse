#ifndef PLUGINHOST_H
#define PLUGINHOST_H

#include "pluginmanager_global.h"


/*!
 * \brief The PluginHost class is an abstract factory for loading objects
 * from plugins.
 *
 * This design allows plugins to be written in multiple languages. To add
 * support for a new language, implement a PluginHost that can load plugins
 * written in that language and implement any required bindings for the
 * element base classes.
 */

class PluginHost
{
public:
    /*!
     * Destroy this PluginHost.
     */
    virtual ~PluginHost() {}

    /*!
     * Analyse the plugin at \a pluginPath and return a PluginData instance
     * describing it. If the file/directory at \a pluginPath is not a plugin
     * that this PluginHost understands, return a default-constructed
     * PluginData instance.
     */
    virtual PluginData getInfo(const QString &pluginPath) = 0;

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
     * Load the given \a plugin and create an instance of the given \a cls.
     */
    virtual QObject*
    instantiateClass(const PluginInfo &plugin, const ClassInfo &cls) = 0;

    typedef std::function<void(QObject*)> Deleter;

    /*!
     * \return a custom deleter function for the instantiated objects.
     */
    virtual Deleter deleter() { return &QObject::deleteLater; }
};

#endif // PLUGINHOST_H
