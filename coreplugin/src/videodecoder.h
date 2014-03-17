#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <elapse/elements/decoder.h>
#include <elapse/displayable.h>


class VideoDecoderPrivate;

/*!
 * \brief The VideoDecoder class decodes the byte stream from the camera.
 *
 * \ingroup core-plugin
 */

class VideoDecoder : public SampleDecoder, public Displayable
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")

public:
    Q_INVOKABLE explicit VideoDecoder(QObject *parent = nullptr);
    ~VideoDecoder();

    QWidget *getWidget();

public slots:
    void onData(QByteArray data);

private:
    VideoDecoderPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(VideoDecoder)
};

#endif // VIDEODECODER_H
