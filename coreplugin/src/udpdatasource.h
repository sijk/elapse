#ifndef UDPDATASOURCE_H
#define UDPDATASOURCE_H

#include <QUdpSocket>
#include <QxtSignalGroup>
#include "elements/datasource.h"


/*!
 * \brief The UdpDataSource class receives data from the device over
 * several UDP sockets - one for each Signal::Type.
 *
 * \ingroup core-plugin
 */

class UdpDataSource : public DataSource
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit UdpDataSource(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void readAndEmit();
    void onSocketError(QAbstractSocket::SocketError err);

private:
    QUdpSocket eegSock;
    QUdpSocket imuSock;
    QUdpSocket videoSock;
    QxtSignalGroup startedSignals;
};

#endif // UDPDATASOURCE_H
