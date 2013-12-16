#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>
#include "elements.h"

class PluginManagerPrivate;


/*!
 * \brief The PluginManager class handles the finding and loading of plugins.
 *
 * \see \ref pluginmanager-model for a detailed description of the internal
 * data model.
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
    void selectPluginsToLoad();
    void loadPluginsFromSettings();

signals:
    void pluginsLoaded(ElementSetPtr elements);

private slots:
    void loadPluginsFromSelection();

private:
    PluginManagerPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(PluginManager)
};

#endif // PLUGINMANAGER_H
