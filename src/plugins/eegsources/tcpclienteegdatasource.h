#ifndef TCPCLIENTEEGDATASOURCE_H
#define TCPCLIENTEEGDATASOURCE_H

#include <QTcpSocket>
#include "datasource.h"

class TcpClientEegDataSource : public DataSource
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TcpClientEegDataSource(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

private slots:
    void onDataReady();
    void onError(QAbstractSocket::SocketError err);

private:
    QTcpSocket sock;
    quint16 _port;
};

#endif // TCPCLIENTEEGDATASOURCE_H
