#include "tcpclientdatasource.h"

/*!
 * Construct a new TcpClientDataSource as a child of the given \a parent.
 */
TcpClientDataSource::TcpClientDataSource(QObject *parent) :
    DataSource(parent),
    eegPort(5000),
    videoPort(6000)
{
    connect(&eegSock, SIGNAL(readyRead()), this, SLOT(onEegReady()));
    connect(&eegSock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    connect(&videoSock, SIGNAL(readyRead()), this, SLOT(onVideoReady()));
    connect(&videoSock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    startedSignals.addSignal(&eegSock, SIGNAL(connected()));
    startedSignals.addSignal(&videoSock, SIGNAL(readyRead()));

    connect(&startedSignals, SIGNAL(allSignalsReceived()), SIGNAL(started()));
    connect(this, SIGNAL(started()), &startedSignals, SLOT(reset()));
    connect(this, SIGNAL(error(QString)), &startedSignals, SLOT(reset()));
}

/*!
 * Connect all of the sockets to their counterparts on the device and start
 * receiving data.
 */
void TcpClientDataSource::start()
{
    eegSock.connectToHost(_host, eegPort);
    videoSock.bind(videoPort);
}

/*!
 * Stop receiving data; close all of the sockets.
 */
void TcpClientDataSource::stop()
{
    eegSock.close();
    videoSock.close();
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
 * Read video datagrams from the socket and emit the videoReady() signal.
 */
void TcpClientDataSource::onVideoReady()
{
    while (videoSock.hasPendingDatagrams()) {
        QByteArray dgram;
        dgram.resize(videoSock.pendingDatagramSize());
        videoSock.readDatagram(dgram.data(), dgram.size());
        emit videoReady(dgram);
    }
}

/*!
 * Emit an error() message when an error occurs on one of the sockets.
 * The host and port will be appended to the error string.
 */
void TcpClientDataSource::onSocketError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    auto sock = qobject_cast<QAbstractSocket*>(sender());

    quint16 port = sock->peerPort();
    if (!port)
        port = sock->localPort();

    QString hostDesc = QStringLiteral(" [%1:%2]").arg(_host).arg(port);
    emit error(sock->errorString() + hostDesc);
}
