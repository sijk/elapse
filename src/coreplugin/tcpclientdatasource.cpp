#include "tcpclientdatasource.h"

/*!
 * Construct a new TcpClientDataSource as a child of the given \a parent.
 */
TcpClientDataSource::TcpClientDataSource(QObject *parent) :
    DataSource(parent),
    eegPort(5000)
{
    connect(&eegSock, SIGNAL(readyRead()), this, SLOT(onEegReady()));
    connect(&eegSock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(&eegSock, SIGNAL(connected()), this, SIGNAL(started()));
}

/*!
 * Connect all of the sockets to their counterparts on the device and start
 * receiving data.
 */
void TcpClientDataSource::start()
{
    eegSock.connectToHost(_host, eegPort);
}

/*!
 * Stop receiving data; close all of the sockets.
 */
void TcpClientDataSource::stop()
{
    eegSock.close();
}

/*!
 * Read EEG data from the socket and emit the eegReady() signal.
 */
void TcpClientDataSource::onEegReady()
{
    if (eegSock.bytesAvailable())
        emit eegReady(eegSock.readAll());
}

/*!
 * Emit an error() message when an error occurs on one of the sockets.
 * The host and port will be appended to the error string.
 */
void TcpClientDataSource::onError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    auto sock = qobject_cast<QTcpSocket*>(sender());
    QString hostDesc = QStringLiteral(" [%1:%2]").arg(_host).arg(eegPort);
    emit error(sock->errorString() + hostDesc);
}
