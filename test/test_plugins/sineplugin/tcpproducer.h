#ifndef TCPPRODUCER_H
#define TCPPRODUCER_H

#include <QtNetwork>
#include "producer.h"

class TcpProducer : public Producer
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TcpProducer(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void readData();
    void showError(QAbstractSocket::SocketError err);

private:
    QTcpSocket *sock;
};

#endif // TCPPRODUCER_H
