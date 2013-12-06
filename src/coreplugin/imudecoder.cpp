#include "sampletypes.h"
#include "imudecoder.h"

ImuDecoder::ImuDecoder(QObject *parent) :
    SampleDecoder(parent)
{
}

void ImuDecoder::onData(const QByteArray &data)
{
    Q_UNUSED(data)
}
