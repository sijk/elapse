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

#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

#include <QStandardItemModel>
#include <memory>
#include <map>
#include "pluginmanager.h"
#include "ui_pluginmanager.h"
#include "pluginmanager_global.h"
#include "pluginhost.h"

namespace elapse { namespace plugin {

class ManagerPrivate
{
public:
    ManagerPrivate(plugin::Manager *q);

    static ManagerPrivate *expose(plugin::Manager *manager);

    Ui::PluginManager ui;
    QDir searchPath;
    std::map<HostID, std::unique_ptr<Host>> hosts;
    QList<PluginData> pluginData;

    void searchForPlugins();
    void populateModels();
    void attachModelViews();

    typedef QPair<const PluginInfo*, const ClassInfo*> ElementInfo;
    typedef QMap<QString, ElementInfo> ElementSetInfo;

    ElementSetInfo getSelectedElements() const;
    ElementSetInfo getSavedElements() const;
    elements::ElementSetPtr createElements(const ElementSetInfo &info);
    void selectElements(const ElementSetInfo &info);
    void saveElements(const ElementSetInfo &info);

    template<class T>
    void createElement(elements::ElementPtr<T> &element, const ElementInfo &info);

    QStandardItem *findItemWithIndices(const QStandardItemModel *model,
                                       int pluginIndex, int classIndex);

    QStandardItemModel dataSourceModel;
    QStandardItemModel dataSinkModel;
    QStandardItemModel eegDecoderModel;
    QStandardItemModel vidDecoderModel;
    QStandardItemModel imuDecoderModel;
    QStandardItemModel eegFeatExModel;
    QStandardItemModel vidFeatExModel;
    QStandardItemModel imuFeatExModel;
    QStandardItemModel classifierModel;
    QStandardItemModel outputActionModel;

    struct ElementData {
        QStandardItemModel *model;
        QTreeView *tree;
        QString elementClass;
        elapse::data::Signal::Type signalType;
        QString elementName;
    };
    QList<ElementData> elements;

private:
    plugin::Manager * const q_ptr;
    Q_DECLARE_PUBLIC(plugin::Manager)
};

}} // namespace elapse::plugin

#endif // PLUGINMANAGER_P_H
