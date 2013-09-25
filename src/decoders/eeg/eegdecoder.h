#ifndef EEGDECODER_H
#define EEGDECODER_H

#include "../decoder.h"

class EegSample;

class EegDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_PROPERTY(quint8 gain MEMBER _gain)
    Q_PROPERTY(double vref MEMBER _vref)

public:
    explicit EegDecoder(QObject *parent = 0);

signals:
    void newSample(const EegSample &sample);

public slots:
    void onData(const QByteArray &data);

private:
    double toMicroVolts(double value) const;
    double _vref;
    quint8 _gain;
};

#endif // EEGDECODER_H
