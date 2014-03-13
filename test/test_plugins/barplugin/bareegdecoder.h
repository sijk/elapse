#ifndef BAREEGDECODER_H
#define BAREEGDECODER_H

#include "elements/decoder.h"


class BarEegDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE explicit BarEegDecoder(QObject *parent = nullptr);

public slots:
    void onData(QByteArray data);
};

#endif // BAREEGDECODER_H
