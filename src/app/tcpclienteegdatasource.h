#ifndef TCPCLIENTEEGDATASOURCE_H
#define TCPCLIENTEEGDATASOURCE_H

#include <QTcpSocket>
#include "datasource.h"

class TcpClientEegDataSource : public DataSource
{
    Q_OBJECT
public:
    explicit TcpClientEegDataSource(QObject *parent = 0);

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
