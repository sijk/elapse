#include "sampletypes.h"
#include "barvideodecoder.h"


BarVideoDecoder::BarVideoDecoder(QObject *parent) :
    SampleDecoder(parent)
{
}

void BarVideoDecoder::onData(QByteArray data)
{
    Q_UNUSED(data);

    auto sample = new VideoSample;
    sample->w = 0;
    sample->h = 0;
    sample->data = QByteArray();

    emit newSample(SamplePtr(sample));
}

