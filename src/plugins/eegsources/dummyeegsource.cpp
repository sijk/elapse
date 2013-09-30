#include <time.h>
#include <cmath>
#include <QDataStream>
#include "sampletypes.h"
#include "dummyeegsource.h"

const uint DummyEegSource::CHUNKSIZE = 25;

DummyEegSource::DummyEegSource(QObject *parent) :
    DataSource(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void DummyEegSource::start()
{
    onTimer();
    timer.start(40);
    emit started();
}

void DummyEegSource::stop()
{
    timer.stop();
}

void DummyEegSource::onTimer()
{
    appendSampleToChunk();
    if (seqnum % CHUNKSIZE == 0) {
        emit eegReady(chunk);
        chunk.clear();
    }
}

void DummyEegSource::appendSampleToChunk()
{
    QDataStream stream(&chunk, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    auto appendBE24 = [&](quint32 value) {
        char bytes[3];
        bytes[0] = (value >> 16) & 0xFF;
        bytes[1] = (value >> 8) & 0xFF;
        bytes[2] = value & 0xFF;
        stream.writeRawData(bytes, 3);
    };

    // Sequence number
    stream << seqnum++;

    // Time stamp
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    quint64 timestamp = time.tv_sec * 1e9 + time.tv_nsec;
    stream << timestamp;

    // Status
    appendBE24(0xC00000);

    // Readings
    for (int i = 0; i < 8; i++) {
        double amplitude = 5e3;
        double period = 250;
        double phase = i * period / 8;
        double omega = 2 * M_PI / period;
        appendBE24(amplitude * std::sin(omega * seqnum - phase));
    }
}
