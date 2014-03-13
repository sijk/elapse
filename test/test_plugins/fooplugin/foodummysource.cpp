#include "sampletypes.h"
#include "foodummysource.h"


FooDummySource::FooDummySource(QObject *parent) :
    DataSource(parent)
{
    connect(&timer, SIGNAL(timeout()), SLOT(emitDummyData()));
}

void FooDummySource::start()
{
    timer.start(500);
    emit started();
}

void FooDummySource::stop()
{
    timer.stop();
}

void FooDummySource::emitDummyData()
{
    emit eegReady(QByteArray());
    emit videoReady(QByteArray());
    emit imuReady(QByteArray());
}
