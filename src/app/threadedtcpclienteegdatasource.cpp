#include "threadedtcpclienteegdatasource.h"

ThreadedTcpClientEegDataSource::ThreadedTcpClientEegDataSource(QObject *parent) :
    DataSource(parent)
{
    connect(&eegThread, SIGNAL(newData(QByteArray)),
            this, SIGNAL(eegReady(QByteArray)));
    connect(&eegThread, SIGNAL(error(int,QString)),
            this, SLOT(onEegError(int,QString)));
}

void ThreadedTcpClientEegDataSource::start()
{
    eegThread.connect();
}

void ThreadedTcpClientEegDataSource::stop()
{
    eegThread.disconnect();
}

void ThreadedTcpClientEegDataSource::setHost(const QString &host)
{
    _host = host;
    eegThread.setHost(_host, 5000);
}

void ThreadedTcpClientEegDataSource::onEegError(int err, const QString &msg)
{
    Q_UNUSED(err)
    emit error(msg);
}
