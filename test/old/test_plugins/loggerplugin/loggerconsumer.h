#ifndef LOGGERCONSUMER_H
#define LOGGERCONSUMER_H

#include <QTimer>
#include "consumer.h"

class LoggerConsumer : public Consumer
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LoggerConsumer(QObject *parent = nullptr);

public slots:
    void onData(double data);
};

#endif // LOGGERCONSUMER_H
