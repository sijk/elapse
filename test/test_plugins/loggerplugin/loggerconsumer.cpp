#include <QDebug>
#include "loggerconsumer.h"

LoggerConsumer::LoggerConsumer(QObject *parent) :
    DataConsumer(parent)
{
}

void LoggerConsumer::onData(double data)
{
    qDebug() << data;
}
