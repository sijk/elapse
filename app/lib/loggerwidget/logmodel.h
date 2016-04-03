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

#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractTableModel>
#include <QxtLogger>

namespace elapse { namespace log {

/*!
 * \brief The LogItem struct represents a logged message.
 * \ingroup logging
 */

struct LogItem {
    QString time;
    QxtLogger::LogLevel level;
    QString message;
};


#define LOG_LEVEL_ROLE  Qt::UserRole


/*!
 * \brief The LogModel class stores LogItem%s in a table model.
 * \ingroup logging
 */

class LogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit LogModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void appendItem(const LogItem &item);

private:
    QList<LogItem> _items;
};

}} // namespace elapse::log

#endif // LOGMODEL_H
