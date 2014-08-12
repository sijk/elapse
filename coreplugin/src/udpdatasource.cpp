#include "udpdatasource.h"

#define EEG_PORT    5000
#define IMU_PORT    6000
#define VIDEO_PORT  7000


/*!
 * Construct a new UdpDataSource.
 */
UdpDataSource::UdpDataSource()
{
    connect(&eegSock,   SIGNAL(readyRead()), SLOT(readAndEmit()));
    connect(&imuSock,   SIGNAL(readyRead()), SLOT(readAndEmit()));
    connect(&videoSock, SIGNAL(readyRead()), SLOT(readAndEmit()));

    connect(&eegSock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(&imuSock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(&videoSock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    startedSignals.addSignal(&eegSock, SIGNAL(readyRead()));
    startedSignals.addSignal(&imuSock, SIGNAL(readyRead()));
    startedSignals.addSignal(&videoSock, SIGNAL(readyRead()));

    connect(&startedSignals, SIGNAL(allSignalsReceived()), SIGNAL(started()));
    connect(this, SIGNAL(started()), &startedSignals, SLOT(reset()));
    connect(this, SIGNAL(error(QString)), &startedSignals, SLOT(reset()));
}

/*!
 * Start listening for data on all of the sockets.
 */
void UdpDataSource::start()
{
    eegSock.bind(QHostAddress::AnyIPv4, EEG_PORT);
    imuSock.bind(QHostAddress::AnyIPv4, IMU_PORT);
    videoSock.bind(QHostAddress::AnyIPv4, VIDEO_PORT);
}

/*!
 * Stop receiving data; close all of the sockets.
 */
void UdpDataSource::stop()
{
    eegSock.close();
    imuSock.close();
    videoSock.close();

    startedSignals.reset();
}

/*!
 * Read data from the socket which called this slot and emit the appropriate
 * signal.
 */
void UdpDataSource::readAndEmit()
{
    QUdpSocket *sock = qobject_cast<QUdpSocket*>(sender());
    Q_ASSERT(sock);

    while (sock->hasPendingDatagrams()) {
        QByteArray dgram;
        dgram.resize(sock->pendingDatagramSize());
        sock->readDatagram(dgram.data(), dgram.size());

        if (sock == &eegSock)
            emit eegReady(dgram);
        else if (sock == &imuSock)
            emit imuReady(dgram);
        else if (sock == &videoSock)
            emit videoReady(dgram);
        else
            Q_UNREACHABLE();
    }
}

/*!
 * Emit an error() message when an error occurs on one of the sockets.
 */
void UdpDataSource::onSocketError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    auto sock = qobject_cast<QUdpSocket*>(sender());
    Q_ASSERT(sock);
    emit error(sock->errorString());
}

