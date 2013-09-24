#include <QtNetwork>
#include "eegthread.h"

EegThread::EegThread(QObject *parent) :
    QThread(parent)
{
}

EegThread::~EegThread()
{
    stopReceiving();
    wait();
}

void EegThread::run()
{
    QTcpSocket sock;

    mutex.lock();
    QString serverName = hostName;
    quint16 serverPort = port;
    QString serverDesc = QStringLiteral(" [%2:%3]").arg(hostName).arg(port);
    mutex.unlock();

    sock.connectToHost(serverName, serverPort);
    if (!sock.waitForConnected(1000)) {
        emit error(sock.error(), sock.errorString() + serverDesc);
        return;
    }

    while (!quit && sock.isOpen()) {
        while (!sock.bytesAvailable()) {
            if (!sock.waitForReadyRead(500)) {
                emit error(sock.error(), sock.errorString() + serverDesc);
                sock.close();
                return;
            }
        }

        mutex.lock();
        QByteArray data = sock.readAll();
        emit newData(data);
        mutex.unlock();
    }

    sock.close();
}

void EegThread::setHost(const QString &name, quint16 port)
{
    QMutexLocker locker(&mutex);
    this->hostName = name;
    this->port = port;
}

void EegThread::startReceiving()
{
    QMutexLocker locker(&mutex);
    if (!isRunning()) {
        quit = false;
        start();
    }
}

void EegThread::stopReceiving()
{
    QMutexLocker locker(&mutex);
    quit = true;
}
