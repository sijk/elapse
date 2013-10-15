#include <time.h>
#include <cmath>
#include <QDataStream>
#include <QtEndian>
#include <QTimer>
#include "sampletypes.h"
#include "dummyeegsource.h"

#define SAMPLE_SIZE     39
#define SAMPLE_RATE     250
#define CHUNK_SIZE      25
#define N_CHANNELS      8


/*!
 * \class DummyEegSource
 * \ingroup core-plugins
 * \inmodule elapse-core
 */


DummyEegSource::DummyEegSource(QObject *parent) :
    DataSource(parent),
    seqnum(0)
{
    chunk.reserve(CHUNK_SIZE * SAMPLE_SIZE);
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void DummyEegSource::start()
{
    onTimer();
    timer.start(1e3 / SAMPLE_RATE);
    QTimer::singleShot(0, this, SIGNAL(started()));
}

void DummyEegSource::stop()
{
    timer.stop();
}

void DummyEegSource::onTimer()
{
    appendSampleToChunk();

    if (seqnum % CHUNK_SIZE == 0) {
        emit eegReady(chunk);
        chunk.clear();
    }
}

void DummyEegSource::appendSampleToChunk()
{
    QDataStream stream(&chunk, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.device()->seek(stream.device()->size());

    auto appendBE24 = [&](qint32 value) {
        const qint32 valueBE = qToBigEndian<qint32>(value);
        stream.writeRawData((const char*)&valueBE + 1, 3);
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
    for (int i = 0; i < N_CHANNELS; i++) {
        double amplitude = 5e3;
        double period = SAMPLE_RATE;
        double omega = 2 * M_PI / period;
        double phase = i * 2 * M_PI * period / N_CHANNELS;
        appendBE24(amplitude * std::sin(omega * seqnum - phase));
    }
}
