#include <elapse/datatypes.h>
#include "bareegdecoder.h"

using elapse::data::EegSample;
using elapse::data::SamplePtr;


BarEegDecoder::BarEegDecoder()
{
}

void BarEegDecoder::onData(QByteArray data)
{
    Q_UNUSED(data);

    for (int i = 0; i < 20; i++) {
        auto sample = EegSample::create();

        sample->seqnum = i;
        sample->timestamp = 0;
        sample->leadOff = 0x00;

        for (int chan = 0; chan < 8; chan++)
            sample->values.push_back(i * 100);

        emit newSample(sample);
    }
}

