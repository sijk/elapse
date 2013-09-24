#include "tcpclienteegdatasource.h"

TcpClientEegDataSource::TcpClientEegDataSource(QObject *parent) :
    DataSource(parent),
    _host("overo.local"),
    _port(5000)
{
    connect(&sock, SIGNAL(readyRead()), this, SLOT(onDataReady()));
    connect(&sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));
}


const QString &TcpClientEegDataSource::host() const
{ return _host; }

quint16 TcpClientEegDataSource::port() const
{ return _port; }

void TcpClientEegDataSource::setHost(const QString &host)
{ _host = host; }

void TcpClientEegDataSource::setPort(quint16 port)
{ _port = port; }


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
    qDebug() << QStringLiteral("Error connecting to %1:%2")
                .arg(_host).arg(_port);
    qDebug() << sock.errorString();
}
