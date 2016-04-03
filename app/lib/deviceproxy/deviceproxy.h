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

#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include <memory>
#include <QObject>
#include <QList>
#include <QTimer>
#include "common/hardware.h"

namespace elapse { namespace client {

namespace dbus { class Device; }


/*!
 * \brief The DeviceProxy class provides an interface to the device over D-Bus.
 * \ingroup app
 */

class DeviceProxy : public QObject
{
    Q_OBJECT
public:
    explicit DeviceProxy(QObject *parent = nullptr);
    ~DeviceProxy();

    hardware::Device *device() const;

    QString deviceAddress() const;
    QString localAddress() const;

    QMap<QString, QVariantMap> getDeviceConfig() const;

public slots:
    void connectTo(const QString &hostname);
    void disconnect();

signals:
    void connected();
    void disconnected();
    void error(QString msg);

private slots:
    void checkConnectivity();

private:
    void connectInBackground();
    bool detectLocalAddressByConnectingTo(const QString& host, quint16 port);

    std::unique_ptr<dbus::Device> dev;
    QString deviceAddr;
    QString localAddr;
    QTimer connectionChecker;
};

}} // namespace elapse::client

#endif // DEVICEPROXY_H
