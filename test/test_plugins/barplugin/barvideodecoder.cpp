#include <elapse/sampletypes.h>
#include "barvideodecoder.h"

using elapse::data::VideoSample;
using elapse::data::SamplePtr;


BarVideoDecoder::BarVideoDecoder()
{
}

void BarVideoDecoder::onData(QByteArray data)
{
    Q_UNUSED(data);

    auto sample = VideoSample::create();
    sample->w = 0;
    sample->h = 0;
    sample->data = QByteArray();

    emit newSample(sample);
}

