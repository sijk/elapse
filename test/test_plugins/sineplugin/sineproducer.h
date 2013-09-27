#ifndef SINEPROVIDER_H
#define SINEPROVIDER_H

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

#endif // SINEPROVIDER_H
