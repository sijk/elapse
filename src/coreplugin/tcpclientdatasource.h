#ifndef TCPCLIENTDATASOURCE_H
#define TCPCLIENTDATASOURCE_H

#include <QTcpSocket>
#include "elements/datasource.h"

class TcpClientDataSource : public DataSource
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TcpClientDataSource(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void onDataReady();
    void onError(QAbstractSocket::SocketError err);

private:
    QTcpSocket eegSock;
    quint16 eegPort;
};

#endif // TCPCLIENTDATASOURCE_H
