#ifndef EEGDECODER_H
#define EEGDECODER_H

#include "elements/decoder.h"

class EegSample;


/*!
 * \brief The EegDecoder class decodes the byte stream from the EEG hardware.
 *
 * \ingroup core-plugins
 */

class EegDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "EEG")
    Q_PROPERTY(quint8 gain MEMBER _gain)
    Q_PROPERTY(double vref MEMBER _vref)

public:
    Q_INVOKABLE explicit EegDecoder(QObject *parent = nullptr);

public slots:
    void onData(const QByteArray &data);

private:
    double toMicroVolts(double value) const;
    double _vref;
    quint8 _gain;
};

#endif // EEGDECODER_H
