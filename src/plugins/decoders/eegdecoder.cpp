#include <QDataStream>
#include "sampletypes.h"
#include "util/bigendian24.h"
#include "eegdecoder.h"

#include <QDebug>


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
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd()) {
        EegSample sample;

        stream >> sample.seqnum;
        stream >> sample.timestamp;

        stream >> value;
        status = value.to32bit();
        sample.loff_stat_p = (status >> 12) & 0xFF;
        sample.loff_stat_n = (status >> 4) & 0xFF;
        sample.gpio = status & 0x0F;

        for (int i = 0; i < 8; i++) {
            stream >> value;
            sample.values.append(toMicroVolts(value.to32bit()));
        }

        checkSequenceNumber(sample);
        emit newSample(sample);
    }
}

double EegDecoder::toMicroVolts(double reading) const
{
    return reading / _gain * _vref / ((1 << 23) - 1);
}
