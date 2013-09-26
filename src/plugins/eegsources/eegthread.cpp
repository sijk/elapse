#include <QtNetwork>
#include "eegthread.h"

EegThread::EegThread(QObject *parent) :
    QThread(parent)
{
}

EegThread::~EegThread()
{
    disconnect();
    wait();
}

void EegThread::run()
{
    QTcpSocket sock;

    mutex.lock();
    QString hostName = this->hostName;
    quint16 port = this->port;
    QString hostDesc = QStringLiteral(" [%2:%3]").arg(hostName).arg(port);
    mutex.unlock();

    sock.connectToHost(hostName, port);
    if (!sock.waitForConnected(1000)) {
        emit error(sock.error(), sock.errorString() + hostDesc);
        return;
    }

    emit connected();

    while (!quit && sock.isOpen()) {
        while (!sock.bytesAvailable()) {
            if (!sock.waitForReadyRead(500)) {
                emit error(sock.error(), sock.errorString() + hostDesc);
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

void EegThread::setHost(const QString &hostName, quint16 port)
{
    QMutexLocker locker(&mutex);
    this->hostName = hostName;
    this->port = port;
}

void EegThread::connect()
{
    QMutexLocker locker(&mutex);
    if (!isRunning()) {
        quit = false;
        start();
    }
}

void EegThread::disconnect()
{
    QMutexLocker locker(&mutex);
    quit = true;
}
