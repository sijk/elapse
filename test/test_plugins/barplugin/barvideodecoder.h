#ifndef BARVIDEODECODER_H
#define BARVIDEODECODER_H

#include <elapse/elements/decoder.h>


class BarVideoDecoder : public elapse::elements::SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")

public:
    Q_INVOKABLE BarVideoDecoder();

public slots:
    void onData(QByteArray data);
};

#endif // BARVIDEODECODER_H
