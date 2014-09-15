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

}} // namespace elapse::coreplugin

#endif // UDPDATASOURCE_H
