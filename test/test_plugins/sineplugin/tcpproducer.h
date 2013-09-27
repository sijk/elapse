#ifndef TCPPROVIDER_H
#define TCPPROVIDER_H

#include <QtNetwork>
#include "producer.h"

class TcpProducer : public Producer
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TcpProducer(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void readData();
    void showError(QAbstractSocket::SocketError err);

private:
    QTcpSocket *sock;
};

#endif // TCPPROVIDER_H
