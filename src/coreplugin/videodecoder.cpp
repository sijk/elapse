#include "sampletypes.h"
#include "videodecoder.h"

VideoDecoder::VideoDecoder(QObject *parent) :
    SampleDecoder(parent)
{
}

void VideoDecoder::onData(QByteArray data)
{
    Q_UNUSED(data)
}
