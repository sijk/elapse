#include "tcpclientdatasource.h"

TcpClientDataSource::TcpClientDataSource(QObject *parent) :
    DataSource(parent),
    eegPort(5000)
{
    connect(&eegSock, SIGNAL(readyRead()), this, SLOT(onDataReady()));
    connect(&eegSock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(&eegSock, SIGNAL(connected()), this, SIGNAL(started()));
}

void TcpClientDataSource::start()
{
    eegSock.connectToHost(_host, eegPort);
}

void TcpClientDataSource::stop()
{
    eegSock.close();
}

void TcpClientDataSource::onDataReady()
{
    if (eegSock.bytesAvailable())
        emit eegReady(eegSock.readAll());
}

void TcpClientDataSource::onError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());
    QString hostDesc = QStringLiteral(" [%1:%2]").arg(_host).arg(eegPort);
    emit error(sock->errorString() + hostDesc);
}
