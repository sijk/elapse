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

#ifndef UDPDATASOURCE_H
#define UDPDATASOURCE_H

#include <QUdpSocket>
#include <QxtSignalGroup>
#include <elapse/elements/datasource.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The UdpDataSource class receives data from the device over
 * several UDP sockets - one for each Signal::Type.
 *
 * \ingroup core-plugin
 */

class UdpDataSource : public elements::DataSource
{
    Q_OBJECT
public:
    Q_INVOKABLE UdpDataSource();

public slots:
    void start() override;
    void stop() override;

private slots:
    void readAndEmit();
    void onSocketError(QAbstractSocket::SocketError err);

private:
    QUdpSocket eegSock;
    QUdpSocket imuSock;
    QUdpSocket videoSock;
    QxtSignalGroup startedSignals;
};

}} // namespace elapse::coreplugin

#endif // UDPDATASOURCE_H
