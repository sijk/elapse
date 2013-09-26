#ifndef LOGGERCONSUMER_H
#define LOGGERCONSUMER_H

#include <QTimer>
#include "dataconsumer.h"

class LoggerConsumer : public DataConsumer
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LoggerConsumer(QObject *parent = 0);

public slots:
    void onData(double data);
};

#endif // LOGGERCONSUMER_H
