#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>
#include "elementset.h"

class PluginManagerPrivate;


/*!
 * \brief The PluginManager class handles the finding and loading of plugins.
 *
 * The PluginManager has multiple PluginHost%s which do the actual work of
 * finding and loading plugins. The PluginManager presents a unified interface
 * to the collection of PluginHost%s, distributing work to them and
 * aggregating the results.
 *
 * The PluginManager also provides two ways to select which elements to load
 * from plugins. Firstly, it presents a GUI that lists the available
 * implementations for each type of element and allows the user to select them.
 * Secondly, it can load the most recently used set of elements from the
 * settings file.
 *
 * \ingroup plugins-int
 */

class PluginManager : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QDir searchPath READ searchPath WRITE setSearchPath)

public:
    explicit PluginManager(QWidget *parent = nullptr);
    ~PluginManager();

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
    PluginManagerPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(PluginManager)
};

#endif // PLUGINMANAGER_H
