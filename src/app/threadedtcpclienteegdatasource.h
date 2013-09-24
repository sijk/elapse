#ifndef THREADEDTCPCLIENTEEGDATASOURCE_H
#define THREADEDTCPCLIENTEEGDATASOURCE_H

#include "eegthread.h"
#include "datasource.h"

class ThreadedTcpClientEegDataSource : public DataSource
{
    Q_OBJECT
    Q_PROPERTY(QString host MEMBER _host WRITE setHost)

public:
    explicit ThreadedTcpClientEegDataSource(QObject *parent = 0);

signals:
    void error(const QString &message);

public slots:
    void start();
    void stop();

    void setHost(const QString &host);

private slots:
    void onEegError(int err, const QString &msg);

private:
    EegThread eegThread;
    QString _host;
};

#endif // THREADEDTCPCLIENTEEGDATASOURCE_H
