#include "sampletypes.h"
#include "bareegdecoder.h"


BarEegDecoder::BarEegDecoder(QObject *parent) :
    SampleDecoder(parent)
{
}

void BarEegDecoder::onData(QByteArray data)
{
    Q_UNUSED(data);

    for (int i = 0; i < 20; i++) {
        auto sample = new EegSample;

        sample->seqnum = i;
        sample->timestamp = 0;
        sample->leadOff = 0x00;

        for (int chan = 0; chan < 8; chan++)
            sample->values.append(i * 100);

        emit newSample(SamplePtr(sample));
    }
}

