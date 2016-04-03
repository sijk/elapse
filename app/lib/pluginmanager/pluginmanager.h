/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDialog>
#include <QDir>
#include <QScopedPointer>
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
    void elementsLoaded(elapse::elements::ElementSetPtr elements);

private slots:
    void loadElementsFromGuiSelection();

private:
    const QScopedPointer<ManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Manager)
};

}} // namespace elapse::plugin

#endif // PLUGINMANAGER_H
