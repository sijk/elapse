#ifndef SINEPRODUCER_H
#define SINEPRODUCER_H

#include <QTimer>
#include "producer.h"

class SineProducer : public Producer
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SineProducer(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void onTimer();

private:
    QTimer t;
};

#endif // SINEPRODUCER_H
