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
 * Unregister this logger engine and destroys it.
 */
TableModelLoggerEngine::~TableModelLoggerEngine()
{
    qxtLog->removeLoggerEngine(this);
    delete _model;
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
    return _model;
}

}} // namespace elapse::log
