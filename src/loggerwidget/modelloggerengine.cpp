#include "logmodel.h"
#include "modelloggerengine.h"

#include <QTextStream>

ModelLoggerEngine::ModelLoggerEngine() :
    _model(new LogModel)
{
    setLogLevelsEnabled(QxtLogger::AllLevels);
    enableLogging();
}

ModelLoggerEngine::~ModelLoggerEngine()
{
    delete _model;
}

void ModelLoggerEngine::initLoggerEngine()
{
    return;  // Move along, nothing to see here.
}

void ModelLoggerEngine::killLoggerEngine()
{
    return;  // Move along, nothing to see here.
}

bool ModelLoggerEngine::isInitialized() const
{
    return true;
}

void ModelLoggerEngine::writeFormatted(QxtLogger::LogLevel level,
                                       const QList<QVariant> &messages)
{
    LogItem item;

    item.level = level;
    item.time = QTime::currentTime();

    QTextStream message(&item.message);
    foreach (QVariant msg, messages) {
        message << msg.toString() << " ";
    }

    _model->appendItem(item);
}

QAbstractItemModel *ModelLoggerEngine::model()
{
    return _model;
}
