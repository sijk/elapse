#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>

namespace elapse { namespace plugin {

/*!
 * \brief The plugin::Interface interface is implemented by all plugins
 * written in C++.
 *
 * A plugin is simply a shared library containing one or more classes, and the
 * plugin::Interface exposes a list of those classes to the host application.
 *
 * \headerfile elapse/plugin.h
 * \ingroup plugins-ext
 */

class Interface
{
public:
    typedef QList<QMetaObject> ClassList;

    /*!
     * \return a list of QMetaObjects representing the classes that this plugin
     * provides.
     * \see ELAPSE_EXPORT_CLASSES
     */
    virtual ClassList classes() = 0;
};


namespace detail {

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
    static Interface::ClassList get()
    {
        Q_STATIC_ASSERT((std::is_base_of<QObject,T1>::value));
        return Interface::ClassList() << T1::staticMetaObject
                                      << MetaObjects<Tn...>::get();
    }
};

template<> struct MetaObjects<>
{
    static Interface::ClassList get() { return {}; }
};

} // namespace detail
}} // namespace elapse::plugin

/*!
 * \brief The interface ID of the elapse::plugin::Interface.
 *
 * All plugins must include the line
 * \code Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid) \endcode after the
 * \c Q_OBJECT macro.
 *
 * \ingroup plugins-ext
 */

#define ElapsePluginInterface_iid "org.nzbri.elapse.PluginInterface"
Q_DECLARE_INTERFACE(elapse::plugin::Interface, ElapsePluginInterface_iid)


/*!
 * Implement elapse::plugin::Interface::classes(), returning the
 * staticMetaObjects of the given classes.
 * \ingroup plugins-ext
 */
#define ELAPSE_EXPORT_CLASSES(...) \
    ClassList classes() { \
        return elapse::plugin::detail::MetaObjects<__VA_ARGS__>::get(); \
    }

#endif // PLUGIN_H
