#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include "elements/decoder.h"


/*!
 * \brief The VideoDecoder class decodes the byte stream from the camera.
 *
 * \ingroup core-plugin
 */

class VideoDecoder : public SampleDecoder
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "VIDEO")

public:
    Q_INVOKABLE explicit VideoDecoder(QObject *parent = nullptr);

public slots:
    void onData(QByteArray data);
};

#endif // VIDEODECODER_H
