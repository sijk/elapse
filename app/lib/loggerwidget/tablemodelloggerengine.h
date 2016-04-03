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

#ifndef TABLEMODELLOGGERENGINE_H
#define TABLEMODELLOGGERENGINE_H

#include <memory>
#include <QxtLoggerEngine>

class QAbstractItemModel;

namespace elapse { namespace log {

class LogModel;


/*!
 * \brief The TableModelLoggerEngine class is a QxtLoggerEngine that stores
 * messages in a table model.
 * \ingroup logging
 */

class TableModelLoggerEngine : public QxtLoggerEngine
{
public:
    TableModelLoggerEngine();
    ~TableModelLoggerEngine();

    void initLoggerEngine() override;
    void killLoggerEngine() override;
    bool isInitialized() const override;
    void writeFormatted(QxtLogger::LogLevel level,
                        const QList<QVariant> &messages) override;

    QAbstractItemModel *model();

private:
    std::unique_ptr<LogModel> _model;
};

}} // namespace elapse::log

#endif // TABLEMODELLOGGERENGINE_H
