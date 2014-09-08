#ifndef FOOEEGDECODER_H
#define FOOEEGDECODER_H

#include <elapse/elements/decoder.h>


class FooEegDecoder : public elapse::elements::SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE FooEegDecoder();

public slots:
    void onData(QByteArray data);
};

#endif // FOOEEGDECODER_H
