#include <QDebug>
#include "loggerconsumer.h"

LoggerConsumer::LoggerConsumer(QObject *parent) :
    Consumer(parent)
{
}

void LoggerConsumer::onData(double data)
{
    qDebug() << data;
}
