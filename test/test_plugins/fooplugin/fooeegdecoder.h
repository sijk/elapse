#ifndef FOOEEGDECODER_H
#define FOOEEGDECODER_H

#include "elements/decoder.h"


class FooEegDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE explicit FooEegDecoder(QObject *parent = nullptr);

public slots:
    void onData(QByteArray data);
};

#endif // FOOEEGDECODER_H
