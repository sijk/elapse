#include <QDataStream>
#include <QxtLogger>
#include "sampletypes.h"
#include "util/bigendian24.h"
#include "eegdecoder.h"

#define CHANNELS_PER_CHIP   8


/*!
 * Check whether the current \a sample has a sequence number exactly one greater
 * than that of the previous sample, and log a warning message if it's not.
 */
void checkSequenceNumber(const EegSample *sample)
{
    static quint32 prev_seqnum = 0;

    int dropped = sample->seqnum - prev_seqnum - 1;
    if (dropped)
        qxtLog->debug(dropped, "dropped samples");

    prev_seqnum = sample->seqnum;
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
 * \property EegDecoder::nChannels
 * The number of EEG channels that the device has.
 */

/*!
 * Decode the given \a data and emit \ref EegSample "EegSamples".
 */
void EegDecoder::onData(QByteArray data)
{
    BigEndian24 be24;
    quint32 status;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd()) {
        auto sample = new EegSample;

        stream >> sample->seqnum;
        stream >> sample->timestamp;

        for (uint chip = 0; chip < _nChannels / CHANNELS_PER_CHIP; chip++) {
            stream >> be24;
            status = be24.to32bit();
            quint8 loffStatP = (status >> 12) & 0xFF;
            sample->leadOff |= loffStatP << (CHANNELS_PER_CHIP * chip);

            for (uint channel = 0; channel < CHANNELS_PER_CHIP; channel++) {
                stream >> be24;
                sample->values.append(toMicroVolts(be24.to32bit()));
            }
        }

        checkSequenceNumber(sample);
        emit newSample(SamplePtr(sample));
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
