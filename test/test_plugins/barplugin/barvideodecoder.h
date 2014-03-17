#ifndef BARVIDEODECODER_H
#define BARVIDEODECODER_H

#include <elapse/elements/decoder.h>


class BarVideoDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")

public:
    Q_INVOKABLE explicit BarVideoDecoder(QObject *parent = nullptr);

public slots:
    void onData(QByteArray data);
};

#endif // BARVIDEODECODER_H
