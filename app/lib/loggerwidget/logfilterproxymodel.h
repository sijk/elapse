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

#ifndef LOGFILTERPROXYMODEL_H
#define LOGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QxtLogger>

namespace elapse { namespace log {

/*!
 * \brief The LogFilterProxyModel class filters the LogModel by log level.
 *
 * All messages in the source model with level less than minimumLogLevel()
 * will be hidden. The default minimum log level is \c InfoLevel. Changes to
 * the minimum log level are persistent between application restarts.
 *
 * \ingroup logging
 */

class LogFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit LogFilterProxyModel(QObject *parent = 0);

    QxtLogger::LogLevel minimumLogLevel() const;
    void setMinimumLogLevel(QxtLogger::LogLevel level);

protected:
    bool filterAcceptsRow(int srcRow, const QModelIndex &srcParent) const override;

private:
    QxtLogger::LogLevel minLevel;
};

}} // namespace elapse::log

#endif // LOGFILTERPROXYMODEL_H
