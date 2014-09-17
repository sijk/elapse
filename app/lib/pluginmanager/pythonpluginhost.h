#ifndef PYTHONPLUGINHOST_H
#define PYTHONPLUGINHOST_H

#include "pluginhost.h"

namespace elapse { namespace plugin {

/*!
 * \brief The PythonHost class loads plugins implemented in Python.
 *
 * The PythonHost internally launches a Python interpreter which is used
 * to load Python packages. A plugin is a Python package containing a list of
 * class objects called `classes`.
 *
 * \note Python plugins must be packages, not modules — i.e.
 * \c "foo/__init__.py" not \c "foo.py".
 *
 * \ingroup plugins-int
 */

class PythonHost : public Host
{
public:
    PythonHost();

protected:
    PluginData getInfo(const QString &pluginPath);
    QObject *instantiateClass(const PluginInfo &plugin, const ClassInfo &cls);
    elements::ElementDeleter deleter();
};

}} // namespace elapse::plugin

#endif // PYTHONPLUGINHOST_H
