#include <QDataStream>
#include "sampletypes.h"
#include "util/bigendian24.h"
#include "eegdecoder.h"

#include <QDebug>


/*!
 * Check whether the current \a sample has a sequence number exactly one greater
 * than that of the previous sample, and log a warning message if it's not.
 */
void checkSequenceNumber(const EegSample &sample)
{
    static quint32 prev_seqnum = 0;

    int dropped = sample.seqnum - prev_seqnum - 1;
    if (dropped)
        qDebug() << "Dropped" << dropped << "samples";

    prev_seqnum = sample.seqnum;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*!
 * Construct a new EegDecoder as a child of the given \a parent.
 */
EegDecoder::EegDecoder(QObject *parent) :
    SampleDecoder(parent),
    _vref(0),
    _gain(1)
{
}

/*!
 * \property EegDecoder::gain
 * The device's current gain setting for all channels.
 */

/*!
 * \property EegDecoder::vref
 * The device's current reference voltage in microvolts.
 */

/*!
 * Decode the given \a data and emit \ref EegSample "EegSamples".
 */
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

/*!
 * \return the \a reading converted to microvolts, given the current gain()
 * and vref().
 */
double EegDecoder::toMicroVolts(double reading) const
{
    return reading / _gain * _vref / ((1 << 23) - 1);
}
