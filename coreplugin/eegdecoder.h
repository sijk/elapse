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

public:
    Q_INVOKABLE EegDecoder();
    ~EegDecoder();

    void configure(QMap<QString, QVariantMap> config) override;

    QWidget *getWidget() override;

public slots:
    void onData(QByteArray data) override;

private:
    const QScopedPointer<EegDecoderPrivate> d_ptr;
    Q_DECLARE_PRIVATE(EegDecoder)
};

}} // namespace elapse::coreplugin

#endif // EEGDECODER_H
