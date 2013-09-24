#ifndef TCPCLIENTEEGDATASOURCE_H
#define TCPCLIENTEEGDATASOURCE_H

#include <QTcpSocket>
#include "datasource.h"

class TcpClientEegDataSource : public DataSource
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost)
    Q_PROPERTY(quint16 port READ port WRITE setPort)

public:
    explicit TcpClientEegDataSource(QObject *parent = 0);

    const QString &host() const;
    quint16 port() const;

public slots:
    void setHost(const QString &host);
    void setPort(quint16 port);

    void start();
    void stop();

private slots:
    void onDataReady();
    void onError(QAbstractSocket::SocketError err);

private:
    QTcpSocket sock;
    QString _host;
    quint16 _port;
};

#endif // TCPCLIENTEEGDATASOURCE_H
