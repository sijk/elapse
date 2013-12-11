#ifndef IMUDECODER_H
#define IMUDECODER_H

#include "elements/decoder.h"


/*!
 * \brief The ImuDecoder class decodes the byte stream from the IMU.
 *
 * \ingroup core-plugin
 */

class ImuDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "IMU")

public:
    Q_INVOKABLE explicit ImuDecoder(QObject *parent = nullptr);

public slots:
    void onData(QByteArray data);
};

#endif // IMUDECODER_H
