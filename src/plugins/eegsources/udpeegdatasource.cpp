#include "udpeegdatasource.h"

UdpEegDataSource::UdpEegDataSource(QObject *parent) :
    DataSource(parent),
    do_emit(false)
{
    sock.bind(QHostAddress::AnyIPv4, 5000);
    connect(&sock, SIGNAL(readyRead()), this, SLOT(onDataReady()));
}

void UdpEegDataSource::start()
{ do_emit = true; }

void UdpEegDataSource::stop()
{ do_emit = false; }

void UdpEegDataSource::onDataReady()
{
    while (sock.hasPendingDatagrams()) {
        QByteArray bytes;
        bytes.resize(sock.pendingDatagramSize());
        sock.readDatagram(bytes.data(), bytes.size());
        if (do_emit)
            emit eegReady(bytes);
    }
}
