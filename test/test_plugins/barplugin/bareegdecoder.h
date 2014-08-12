#ifndef BAREEGDECODER_H
#define BAREEGDECODER_H

#include <elapse/elements/decoder.h>


class BarEegDecoder : public elapse::SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE BarEegDecoder();

public slots:
    void onData(QByteArray data);
};

#endif // BAREEGDECODER_H
