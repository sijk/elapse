#include "tcpproducer.h"

TcpProducer::TcpProducer(QObject *parent) :
    Producer(parent),
    sock(new QTcpSocket(this))
{
    connect(sock, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(showError(QAbstractSocket::SocketError)));
}

void TcpProducer::start()
{
    sock->connectToHost("localhost", 2468);
}

void TcpProducer::stop()
{
    sock->disconnectFromHost();
}

void TcpProducer::readData()
{
    double data;

    if (sock->bytesAvailable() < (int)sizeof(double))
        return;

    sock->read((char*)&data, sizeof(double));
    emit dataReady(data);
}

void TcpProducer::showError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err);
    qDebug() << "SocketError:" << sock->errorString();
}

