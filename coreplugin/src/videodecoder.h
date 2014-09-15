#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <elapse/elements/decoder.h>
#include <elapse/displayable.h>

namespace elapse { namespace coreplugin {

class VideoDecoderPrivate;

/*!
 * \brief The VideoDecoder class decodes the byte stream from the camera.
 *
 * \ingroup core-plugin
 */

class VideoDecoder : public elements::SampleDecoder,
                     public elapse::Displayable
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")

public:
    Q_INVOKABLE VideoDecoder();
    ~VideoDecoder();

    QWidget *getWidget();

public slots:
    void start();
    void stop();
    void onData(QByteArray data);

private:
    VideoDecoderPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(VideoDecoder)
};

}} // namespace elapse::coreplugin

#endif // VIDEODECODER_H
