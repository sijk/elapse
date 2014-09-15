#ifndef IMUDECODER_H
#define IMUDECODER_H

#include <elapse/elements/decoder.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The ImuDecoder class decodes the byte stream from the IMU.
 *
 * \ingroup core-plugin
 */

class ImuDecoder : public elements::SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "IMU")

public:
    Q_INVOKABLE ImuDecoder();

public slots:
    void onData(QByteArray data);
};

}} // namespace elapse::coreplugin

#endif // IMUDECODER_H
