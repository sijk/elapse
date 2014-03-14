#ifndef COSINEPRODUCER_H
#define COSINEPRODUCER_H

#include <QTimer>
#include "producer.h"

class CosineProducer : public Producer
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CosineProducer(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void onTimer();

private:
    QTimer t;
};

#endif // COSINEPRODUCER_H
