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

#include <QSettings>
#include "logmodel.h"
#include "logfilterproxymodel.h"

namespace elapse { namespace log {

/*!
 * Construct a new LogFilterProxyModel as a child of the given parent.
 */
LogFilterProxyModel::LogFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    QVariant savedLevel(QSettings().value("logview/level", QxtLogger::InfoLevel));
    minLevel = QxtLogger::LogLevel(savedLevel.toInt());

    setFilterKeyColumn(2);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

/*!
 * Set the minimum log level to \a level. All messages below this level wil be
 * hidden.
 */
void LogFilterProxyModel::setMinimumLogLevel(QxtLogger::LogLevel level)
{
    minLevel = level;
    invalidateFilter();
    QSettings().setValue("logview/level", int(level));
}

/*!
 * \return the current minimum log level.
 */
QxtLogger::LogLevel LogFilterProxyModel::minimumLogLevel() const
{
    return minLevel;
}

/*!
 * \return whether the given log item should be passed through the filter
 * or not.
 */
bool LogFilterProxyModel::filterAcceptsRow(int srcRow,
                                           const QModelIndex &srcParent) const
{
    QModelIndex idx = sourceModel()->index(srcRow, 1, srcParent);
    int level = sourceModel()->data(idx, LOG_LEVEL_ROLE).toInt();

    if (level >= minLevel)
        return QSortFilterProxyModel::filterAcceptsRow(srcRow, srcParent);

    return false;
}

}} // namespace elapse::log
