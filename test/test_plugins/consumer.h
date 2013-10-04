#ifndef DATACONSUMER_H
#define DATACONSUMER_H

#include <QObject>

class Consumer : public QObject
{
    Q_OBJECT
public:
    Consumer(QObject *parent = 0) : QObject(parent) {}

public slots:
    virtual void onData(double data) = 0;
};

#endif // DATACONSUMER_H
