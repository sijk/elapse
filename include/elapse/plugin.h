#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>

namespace elapse {

/*!
 * \brief The PluginInterface class is implemented by all plugins.
 *
 * A plugin is simply a shared library containing one or more classes, and the
 * PluginInterface exposes a list of those classes to the host application.
 *
 * \headerfile elapse/plugin.h
 * \ingroup plugins-ext
 */

class PluginInterface
{
public:
    typedef QList<QMetaObject> ClassList;

    /*!
     * \return a list of QMetaObjects representing the classes that this plugin
     * provides.
     */
    virtual ClassList classes() = 0;
};

} // namespace elapse


/*!
 * \brief The interface ID of the elapse::PluginInterface.
 *
 * All plugins must include the line
 * \code Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid) \endcode after the
 * \c Q_OBJECT macro.
 *
 * \ingroup plugins-ext
 */

#define ElapsePluginInterface_iid "org.nzbri.elapse.PluginInterface"
Q_DECLARE_INTERFACE(elapse::PluginInterface, ElapsePluginInterface_iid)


#ifndef DOXYGEN

namespace elapse {

template<typename... Args> struct MetaObjects;

/*!
 * \brief The MetaObjects struct extracts staticMetaObjects from the classes
 * passed as template arguments.
 *
 * This is a helper for implementing plugins — see ELAPSE_EXPORT_CLASSES()
 * for a friendlier interface to this functionality.
 *
 * It is implemented as a recursive variadic template, so requires a compiler
 * with C++11 support. The template arguments must be subclasses of QObject
 * (enforced at compile time).
 *
 * \ingroup plugins-ext
 */
template <typename T1, typename... Tn>
struct MetaObjects<T1, Tn...>
{
    /*!
     * Extract the QMetaObjects from the template arguments.
     */
    static PluginInterface::ClassList get()
    {
        Q_STATIC_ASSERT((std::is_base_of<QObject,T1>::value));
        return PluginInterface::ClassList() << T1::staticMetaObject
                                            << MetaObjects<Tn...>::get();
    }
};

template<> struct MetaObjects<>
{
    static PluginInterface::ClassList get() { return {}; }
};

} // namespace elapse

#endif


/*!
 * Implement elapse::PluginInterface::classes(), returning the
 * staticMetaObjects of the given \a Classes.
 * \ingroup plugins-ext
 */
#define ELAPSE_EXPORT_CLASSES(Classes...) \
    ClassList classes() { return elapse::MetaObjects<Classes>::get(); }

#endif // PLUGIN_H
