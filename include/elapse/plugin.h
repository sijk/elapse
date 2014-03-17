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
 * All Plugin%s must include the line
 * \code Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid) \endcode after the
 * \c Q_OBJECT macro.
 *
 * \ingroup plugins-ext
 */

#define ElapsePluginInterface_iid "org.nzbri.elapse.PluginInterface"
Q_DECLARE_INTERFACE(elapse::PluginInterface, ElapsePluginInterface_iid)


namespace elapse {

/*!
 * \brief The Plugin class is the base class for all plugins.
 *
 * All it does is provide a QObject base class implementing the PluginInterface.
 *
 * \ingroup plugins-ext
 */

class Plugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(elapse::PluginInterface)
};

} // namespace elapse


#endif // PLUGIN_H
