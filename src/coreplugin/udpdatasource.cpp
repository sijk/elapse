#include "udpdatasource.h"

/*!
 * Construct a new UdpDataSource as a child of the given \a parent.
 */
UdpDataSource::UdpDataSource(QObject *parent) :
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

    startedSignals.addSignal(&eegSock, SIGNAL(readyRead()));
//    startedSignals.addSignal(&videoSock, SIGNAL(readyRead()));

    connect(&startedSignals, SIGNAL(allSignalsReceived()), SIGNAL(started()));
    connect(this, SIGNAL(started()), &startedSignals, SLOT(reset()));
    connect(this, SIGNAL(error(QString)), &startedSignals, SLOT(reset()));
}

/*!
 * Start listening for data on all of the sockets.
 */
void UdpDataSource::start()
{
    eegSock.bind(QHostAddress::AnyIPv4, eegPort);
    videoSock.bind(videoPort);
}

/*!
 * Stop receiving data; close all of the sockets.
 */
void UdpDataSource::stop()
{
    eegSock.close();
    videoSock.close();
}

/*!
 * Read EEG data from the socket and emit the eegReady() signal.
 */
void UdpDataSource::onEegReady()
{
    while (eegSock.hasPendingDatagrams()) {
        QByteArray dgram;
        dgram.resize(eegSock.pendingDatagramSize());
        eegSock.readDatagram(dgram.data(), dgram.size());
        emit eegReady(dgram);
    }
}

/*!
 * Read video data from the socket and emit the videoReady() signal.
 */
void UdpDataSource::onVideoReady()
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
void UdpDataSource::onSocketError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    auto sock = qobject_cast<QAbstractSocket*>(sender());

    quint16 port = sock->peerPort();
    if (!port)
        port = sock->localPort();

    QString hostDesc = QStringLiteral(" [%1:%2]").arg(_host).arg(port);
    emit error(sock->errorString() + hostDesc);
}
