#include "tcpprovider.h"

TcpProvider::TcpProvider(QObject *parent) :
    DataProvider(parent),
    sock(new QTcpSocket(this))
{
    connect(sock, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(showError(QAbstractSocket::SocketError)));
}

void TcpProvider::start()
{
    sock->connectToHost("localhost", 2468);
}

void TcpProvider::stop()
{
    sock->disconnectFromHost();
}

void TcpProvider::readData()
{
    double data;

    if (sock->bytesAvailable() < (int)sizeof(double))
        return;

    sock->read((char*)&data, sizeof(double));
    emit dataReady(data);
}

void TcpProvider::showError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err);
    qDebug() << "SocketError:" << sock->errorString();
}

