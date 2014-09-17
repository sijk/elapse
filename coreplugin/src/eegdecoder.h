#ifndef EEGDECODER_H
#define EEGDECODER_H

#include <QScopedPointer>
#include <elapse/elements/decoder.h>
#include <elapse/displayable.h>

namespace elapse { namespace coreplugin {

class EegDecoderPrivate;


/*!
 * \brief The EegDecoder class decodes the byte stream from the EEG hardware.
 *
 * \ingroup core-plugin
 */

class EegDecoder : public elements::SampleDecoder,
                   public elapse::Displayable
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")
    Q_PROPERTY(quint8 gain READ gain WRITE setGain)
    Q_PROPERTY(double vref READ vref WRITE setVref)
    Q_PROPERTY(uint nChannels READ nChannels WRITE setNChannels)

public:
    Q_INVOKABLE EegDecoder();
    ~EegDecoder();

    void configure(QMap<QString, QVariantMap> config);

    quint8 gain() const;
    void setGain(quint8 gain);

    double vref() const;
    void setVref(double vref);

    uint nChannels() const;
    void setNChannels(uint nChannels);

    QWidget *getWidget();

public slots:
    void onData(QByteArray data);

private:
    const QScopedPointer<EegDecoderPrivate> d_ptr;
    Q_DECLARE_PRIVATE(EegDecoder)
};

}} // namespace elapse::coreplugin

#endif // EEGDECODER_H
