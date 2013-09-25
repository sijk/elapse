#include <QDataStream>
#include "sampletypes.h"
#include "eegdecoder.h"

#include <QDebug>


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * Helper class to parse 24-bit big-endian integers from a QDataStream.
 */
struct BigEndian24
{
    char bytes[3];
    inline qint32 to32bit() const;
};

qint32 BigEndian24::to32bit() const
{
    // Set the high 24 bits and then right shift to get correct sign extension
    return ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8)) >> 8;
}

QDataStream &operator>>(QDataStream &stream, BigEndian24 &value)
{
    stream.readRawData(value.bytes, 3);
    return stream;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void checkSequenceNumber(const EegSample &sample)
{
    static quint32 prev_seqnum = 0;

    int dropped = sample.seqnum - prev_seqnum - 1;
    if (dropped)
        qDebug() << "Dropped" << dropped << "samples";

    prev_seqnum = sample.seqnum;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


EegDecoder::EegDecoder(QObject *parent) :
    SampleDecoder(parent)
{
}

void EegDecoder::onData(const QByteArray &data)
{
    BigEndian24 value;
    quint32 status;
    EegSample sample;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd()) {
        stream >> sample.seqnum;
        stream >> sample.timestamp;

        stream >> value;
        status = value.to32bit();
        sample.loff_stat_p = (status >> 12) & 0xFF;
        sample.loff_stat_n = (status >> 4) & 0xFF;
        sample.gpio = status & 0x0F;

        for (int i = 0; i < 8; i++) {
            stream >> value;
            sample.channel.append(toMicroVolts(value.to32bit()));
        }

        checkSequenceNumber(sample);
        emit newSample(sample);
    }
}

double EegDecoder::toMicroVolts(double reading) const
{
    return reading / _gain * _vref / ((1 << 23) - 1);
}
