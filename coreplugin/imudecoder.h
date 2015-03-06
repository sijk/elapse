#ifndef IMUDECODER_H
#define IMUDECODER_H

#include <QScopedPointer>
#include <elapse/elements/decoder.h>

namespace elapse { namespace coreplugin {

class ImuDecoderPrivate;

/*!
 * \brief The ImuDecoder class decodes the byte stream from the IMU.
 *
 * The accelerometer and gyroscope have different sampling rates (!) so the
 * gyroscope data is interpolated to match the timestamps of the accelerometer
 * data.
 *
 * \see splinterp()
 * \ingroup core-plugin
 */

class ImuDecoder : public elements::SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "IMU")

public:
    Q_INVOKABLE ImuDecoder();
    ~ImuDecoder();

public slots:
    void configure(QMap<QString, QVariantMap> config);
    void onData(QByteArray data) override;

private:
    const QScopedPointer<ImuDecoderPrivate> d_ptr;
    Q_DECLARE_PRIVATE(ImuDecoder)
};

}} // namespace elapse::coreplugin

#endif // IMUDECODER_H
