#include <QPointer>
#include <QxtLogger>
#include <QGst/Init>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Pipeline>
#include <QGst/Element>
#include <QGst/Pad>
#include <QGst/Utils/ApplicationSource>
#include <QGst/Utils/ApplicationSink>
#include <QGst/Ui/VideoWidget>
#include <QGst/Bus>
#include <QGst/Parse>
#include <QGst/Message>
#include <elapse/sampletypes.h>
#include "util/gstwrappedbuffer.h"
#include "videodecoder.h"

using elapse::SamplePtr;


#define SRC_CAPS \
    "application/x-rtp, media=(string)video, "\
    "clock-rate=(int)90000, encoding-name=(string)H264, "\
    "sprop-parameter-sets=(string)\"Z0KAHukFD5CAAAH0AAB1MAIA\\,aM48gAA\\=\", "\
    "payload=(int)96"

#define PIPELINE \
    "appsrc name=src ! rtph264depay ! video/x-h264,framerate=60/1 ! " \
    "ffdec_h264 ! videoflip method=upper-left-diagonal ! " \
    "tee name=t  ! queue ! appsink name=appsink " \
    "t. ! queue ! xvimagesink name=displaysink sync=false"

// TODO: Use an rtpjitterbuffer?


/*!
 * \brief The GstVideoSample struct makes a QGst::Buffer look like a VideoSample.
 *
 * It keeps a reference to the QGst::Buffer in order to keep it alive until
 * the VideoSample is destroyed.
 */

struct GstVideoSample : elapse::VideoSample
{
    GstVideoSample(QGst::BufferPtr buffer);

private:
    QGst::BufferPtr buff;
};


/*!
 * \brief The ApplicationSink class turns the "new-buffer" GStreamer signal
 * into a Qt signal.
 *
 * For some reason, using QGlib::connect() on the "new-buffer" appsink signal
 * doesn't work, even if "emit-signals" is true. This class is a work-around.
 */

class ApplicationSink : public QObject, public QGst::Utils::ApplicationSink
{
    Q_OBJECT
protected:
    QGst::FlowReturn newBuffer() { emit bufferReady(); return QGst::FlowOk; }
signals:
    void bufferReady();
};


/*!
 * \brief The VideoDecoderPrivate class hides the implementation details of the
 * VideoDecoder.
 *
 * It manages the GStreamer pipeline that does the actual video decoding.
 *
 * This class must inherit from QObject in order for QGlib::connect() to be
 * able to connect to its instance methods.
 */

class VideoDecoderPrivate : public QObject
{
    Q_OBJECT

    VideoDecoder * const q_ptr;
    Q_DECLARE_PUBLIC(VideoDecoder)

public:
    VideoDecoderPrivate(VideoDecoder *q);
    ~VideoDecoderPrivate();

    QGst::PipelinePtr pipeline;
    QGst::Utils::ApplicationSource appsrc;
    ApplicationSink appsink;
    QPointer<QGst::Ui::VideoWidget> displaysink;
    QSize videoSize;

    void onData(QByteArray data);
    Q_SLOT void onFrameDecoded();
    void onVideoError(const QGst::MessagePtr &msg);
    void onStateChange(const QGst::MessagePtr &msg);
};


/*!
 * Create the GStreamer pipeline which will do the actual video decoding. Also
 * starts the pipeline ready for input.
 */
VideoDecoderPrivate::VideoDecoderPrivate(VideoDecoder *q) :
    q_ptr(q)
{
    QGst::init();

    try {
        pipeline = QGst::Parse::launch(PIPELINE).dynamicCast<QGst::Pipeline>();
    } catch (QGlib::Error &e) {
        qxtLog->error("VideoDecoder:", e.message());
        emit q->error("VideoDecoder: " + e.message());
        return;
    }

    appsrc.setElement(pipeline->getElementByName("src"));
    appsrc.setCaps(QGst::Caps::fromString(SRC_CAPS));
    appsrc.setStreamType(QGst::AppStreamTypeStream);
    appsrc.setFormat(QGst::FormatTime);
    appsrc.setLive(true);

    appsink.setElement(pipeline->getElementByName("appsink"));
    appsink.element()->setProperty("sync", false);
    connect(&appsink, SIGNAL(bufferReady()), SLOT(onFrameDecoded()));

    pipeline->bus()->addSignalWatch();
    QGlib::connect(pipeline->bus(), "message::error",
                   this, &VideoDecoderPrivate::onVideoError);
    QGlib::connect(pipeline->bus(), "message::state-change",
                   this, &VideoDecoderPrivate::onStateChange);

    pipeline->setState(QGst::StatePlaying);
}

/*!
 * Stop the decoding pipeline.
 */
VideoDecoderPrivate::~VideoDecoderPrivate()
{
    if (pipeline) {
        QGlib::disconnect(appsink.element());
        QGlib::disconnect(pipeline->bus());
        pipeline->bus()->removeSignalWatch();
        pipeline->setState(QGst::StateNull);
    }
}

/*!
 * Called when there is data available to be decoded. Wraps the data in a
 * QGst::Buffer and pushes it into the pipeline.
 */
void VideoDecoderPrivate::onData(QByteArray data)
{
    appsrc.pushBuffer(gstBufferFromBytes(data, CopyMethod::Deep));
}

/*!
 * Called when the decoder pipeline has decoded a frame of video. Pulls the
 * frame out of the pipeline, wraps it in a VideoSample, and emits the
 * newSample() signal.
 */
void VideoDecoderPrivate::onFrameDecoded()
{
    Q_Q(VideoDecoder);

    QGst::BufferPtr buff = appsink.pullBuffer();
    if (!buff)
        return;

    auto frame = new GstVideoSample(buff);
    emit q->newSample(SamplePtr(frame));
}

/*!
 * Construct a GstVideoSample which wraps the given \a buffer.
 *
 * This avoids the need to copy data from the QGst::Buffer into the VideoSample.
 */
GstVideoSample::GstVideoSample(QGst::BufferPtr buffer) :
    buff(buffer)
{
    auto caps = buff->caps()->internalStructure(0);

    timestamp = buff->timeStamp();
    w = caps->value("width").toInt();
    h = caps->value("height").toInt();
    data = QByteArray::fromRawData((const char*)buff->data(), buff->size());
}

/*!
 * Called when an error occurs in the GStreamer pipeline. Extracts the error
 * message and emits it as an error() signal.
 */
void VideoDecoderPrivate::onVideoError(const QGst::MessagePtr &msg)
{
    Q_Q(VideoDecoder);
    auto err = msg.staticCast<QGst::ErrorMessage>();

    QString message("VideoDecoder error from %1: %2");
    message = message.arg(err->source()->name()).arg(err->error().message());
    qxtLog->error(message);
    emit q->error(message);

    pipeline->setState(QGst::StateNull);
}

/*!
 * Inspect the negotiated caps of the appsink once playback has started
 * and use this information to set the video widget size.
 */
void VideoDecoderPrivate::onStateChange(const QGst::MessagePtr &msg)
{
    if (msg->source() != pipeline || msg->type() != QGst::MessageStateChanged)
        return;

    auto stateChange = msg.staticCast<QGst::StateChangedMessage>();
    if (stateChange->newState() == QGst::StatePlaying) {
        auto sink = appsink.element()->getStaticPad("sink");
        auto caps = sink->negotiatedCaps()->internalStructure(0);
        videoSize = { caps->value("width").toInt(),
                      caps->value("height").toInt() };
        if (displaysink)
            displaysink->setMinimumSize(videoSize);
    }
}


/*!
 * Create a new VideoDecoder as a child of the given \a parent.
 *
 * Internally, the VideoDecoder uses a QGst::Pipeline to decode the video
 * stream.
 */
VideoDecoder::VideoDecoder(QObject *parent) :
    SampleDecoder(parent),
    d_ptr(new VideoDecoderPrivate(this))
{
}

/*!
 * Destroy this VideoDecoder.
 */
VideoDecoder::~VideoDecoder()
{
    delete d_ptr;
}

/*!
 * Executed when \a data is available for decoding. Feeds the data into the
 * internal decoding pipeline. The newSample() signal will be emitted for each
 * frame of decoded video.
 */
void VideoDecoder::onData(QByteArray data)
{
    Q_D(VideoDecoder);
    d->onData(data);
}

/*!
 * \return a widget displaying the decoded video.
 */
QWidget *VideoDecoder::getWidget()
{
    Q_D(VideoDecoder);
    Q_ASSERT(d->pipeline);
    if (!d->displaysink) {
        d->displaysink = new QGst::Ui::VideoWidget;
        d->displaysink->setVideoSink(d->pipeline->getElementByName("displaysink"));
        d->displaysink->setMinimumSize(100, 100);
        d->displaysink->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    return d->displaysink;
}

#include "videodecoder.moc" // because VideoDecoderPrivate inherits from QObject
