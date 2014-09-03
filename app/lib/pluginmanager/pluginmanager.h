#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>
#include "elementset.h"

namespace elapse {

/*!
 * \brief Dynamically load elapse::elements from plugins.
 */

namespace plugin {

class ManagerPrivate;


/*!
 * \brief The plugin::Manager class handles the finding and loading of plugins.
 *
 * The plugin::Manager has multiple plugin::Host%s which do the actual work of
 * finding and loading plugins. The plugin::Manager presents a unified interface
 * to the collection of plugin::Host%s, distributing work to them and
 * aggregating the results.
 *
 * The plugin::Manager also provides two ways to select which elements to load
 * from plugins. Firstly, it presents a GUI that lists the available
 * implementations for each type of element and allows the user to select them.
 * Secondly, it can load the most recently used set of elements from the
 * settings file.
 *
 * \ingroup plugins-int
 */

class Manager : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QDir searchPath READ searchPath WRITE setSearchPath)

public:
    explicit Manager(QWidget *parent = nullptr);
    ~Manager();

    QDir searchPath() const;
    void setSearchPath(QDir newPath);

public slots:
    void loadElementsFromGui();
    void loadElementsFromSettings();

signals:
    void elementsLoaded(ElementSetPtr elements);

private slots:
    void loadElementsFromGuiSelection();

private:
    ManagerPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(Manager)
};

}} // namespace elapse::plugin

#endif // PLUGINMANAGER_H
