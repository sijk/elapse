#ifndef TCPPROVIDER_H
#define TCPPROVIDER_H

#include <QtNetwork>
#include "dataproviderinterface.h"

class TcpProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit TcpProvider(QObject *parent = 0);

public slots:
    void start();
    void stop();

private slots:
    void readData();
    void showError(QAbstractSocket::SocketError err);

private:
    QTcpSocket *sock;
};

DEFAULT_DATA_PROVIDER_FACTORY(TcpProvider)

#endif // TCPPROVIDER_H
