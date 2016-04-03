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

#include "logmodel.h"
#include "tablemodelloggerengine.h"

#include <QTime>
#include <QTextStream>

namespace elapse { namespace log {

/*!
 * Construct a new TableModelLoggerEngine and instantiate its internal LogModel.
 *
 * The new instance is automatically registered with the QxtLogger framework.
 */
TableModelLoggerEngine::TableModelLoggerEngine() :
    _model(new LogModel)
{
    setLogLevelsEnabled(QxtLogger::AllLevels);
    enableLogging();

    qxtLog->addLoggerEngine("ModelLoggerEngine", this);
}

/*!
 * Unregister this logger engine and destroy it.
 */
TableModelLoggerEngine::~TableModelLoggerEngine()
{
    qxtLog->removeLoggerEngine(this);
}

void TableModelLoggerEngine::initLoggerEngine()
{
    return;  // Move along, nothing to see here.
}

void TableModelLoggerEngine::killLoggerEngine()
{
    return;  // Move along, nothing to see here.
}

bool TableModelLoggerEngine::isInitialized() const
{
    return true;
}

/*!
 * Append the given \a messages to the LogModel.
 */
void TableModelLoggerEngine::writeFormatted(QxtLogger::LogLevel level,
                                            const QList<QVariant> &messages)
{
    LogItem item;

    item.level = level;
    item.time = QTime::currentTime().toString("hh:mm:ss.zzz");

    QTextStream message(&item.message);
    for (const QVariant &msg : messages)
        message << msg.toString() << " ";

    _model->appendItem(item);
}

/*!
 * \return the internal LogModel.
 */
QAbstractItemModel *TableModelLoggerEngine::model()
{
    return _model.get();
}

}} // namespace elapse::log
