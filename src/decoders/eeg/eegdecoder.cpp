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
    inline quint32 toU32() const;
    inline qint32 toS32() const;
};

quint32 BigEndian24::toU32() const
{
    return (bytes[0] << 16) | (bytes[1] << 8) | bytes[2];
}

qint32 BigEndian24::toS32() const
{
    if (bytes[0] & 0x80)
        return (0xFF << 24) | toU32();
    else
        return toU32();
}

QDataStream &operator>>(QDataStream &stream, BigEndian24 &value)
{
    stream.readRawData(value.bytes, 3);
    return stream;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


EegDecoder::EegDecoder(QObject *parent) :
    SampleDecoder(parent)
{ }

QList<quint8> EegDecoder::gains() const
{ return _gains; }

quint8 EegDecoder::gain(int channel) const
{ return _gains[channel]; }

double EegDecoder::vref() const
{ return _vref; }

void EegDecoder::setGains(const QList<quint8> &gains)
{ _gains = gains; }

void EegDecoder::setGain(int channel, quint8 gain)
{ _gains[channel] = gain; }

void EegDecoder::setVref(double vref)
{ _vref = vref; }

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
        status = value.toU32();
        sample.loff_stat_p = (status >> 12) & 0xFF;
        sample.loff_stat_n = (status >> 4) & 0xFF;
        sample.gpio = status & 0x0F;

        for (int i = 0; i < 8; i++) {
            stream >> value;
            sample.channel.append(parseVoltage(i, value.toS32()));
        }

        emit newSample(sample);
    }
}

double EegDecoder::parseVoltage(int channel, double value) const
{
    return value / _gains[channel] * _vref / ((1 << 23) - 1);
}
