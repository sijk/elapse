#ifndef EEGDECODER_H
#define EEGDECODER_H

#include <QList>
#include "../decoder.h"

class EegSample;

class EegDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_PROPERTY(QList<quint8> gains READ gains WRITE setGains)
    Q_PROPERTY(double vref READ vref WRITE setVref)

public:
    explicit EegDecoder(QObject *parent = 0);

    QList<quint8> gains() const;
    quint8 gain(int channel) const;
    double vref() const;

signals:
    void newSample(const EegSample &sample);

public slots:
    void setGains(const QList<quint8> &gains);
    void setGain(int channel, quint8 gain);
    void setVref(double vref);

    void onData(const QByteArray &data);

private:
    double parseVoltage(int channel, double value) const;
    double _vref;
    QList<quint8> _gains;
};

#endif // EEGDECODER_H
