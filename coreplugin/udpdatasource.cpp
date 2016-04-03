/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#include "udpdatasource.h"

#define EEG_PORT    5000
#define IMU_PORT    6000
#define VIDEO_PORT  7000

namespace elapse { namespace coreplugin {

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

}} // namespace elapse::coreplugin
