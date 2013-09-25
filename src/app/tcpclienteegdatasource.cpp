#include "tcpclienteegdatasource.h"

TcpClientEegDataSource::TcpClientEegDataSource(QObject *parent) :
    DataSource(parent),
    _port(5000)
{
    connect(&sock, SIGNAL(readyRead()), this, SLOT(onDataReady()));
    connect(&sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));
}

void TcpClientEegDataSource::start()
{
    sock.connectToHost(_host, _port);
}

void TcpClientEegDataSource::stop()
{
    sock.close();
}

void TcpClientEegDataSource::onDataReady()
{
    if (sock.bytesAvailable())
        emit eegReady(sock.readAll());
}

void TcpClientEegDataSource::onError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    QString hostDesc = QStringLiteral(" [%1:%2]").arg(_host).arg(_port);
    emit error(sock.errorString() + hostDesc);
}
