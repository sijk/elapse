#include <elapse/sampletypes.h>
#include "fooeegdecoder.h"

using elapse::EegSample;
using elapse::SamplePtr;


FooEegDecoder::FooEegDecoder(QObject *parent) :
    SampleDecoder(parent)
{
}

void FooEegDecoder::onData(QByteArray data)
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

