#include <QPointer>
#include <QQueue>
#include <QMutexLocker>
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


/*!
 * \brief The GstVideoSample struct makes a QGst::Buffer look like a
 * VideoSample.
 *
 * It keeps a reference to the QGst::Buffer in order to keep it alive until
 * the VideoSample is destroyed.
 */

struct GstVideoSample : elapse::VideoSample
{
    GstVideoSample(QGst::BufferPtr buffer, elapse::TimeStamp ts);

private:
    QGst::BufferPtr buff;
};


/*!
 * \brief The ApplicationSink class turns the "new-buffer" GStreamer signal
 * into a Qt signal.
 *
 * Unfortunately we can't just QGlib::connect() to the "new-buffer" signal
 * because QtGstreamer uses _set_callbacks() internally which disables appsink
 * signal emission.
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

    QQueue<elapse::TimeStamp> frameTimes;
    QMutex frameTimesLock;  ///< Serialize access to frameTimes.

    void onInputData(QByteArray data);
    Q_SLOT void onFrameDecoded();
    void onGstError(const QGst::MessagePtr &msg);
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
    connect(&appsink, SIGNAL(bufferReady()),
            this, SLOT(onFrameDecoded()), Qt::DirectConnection);

    pipeline->bus()->addSignalWatch();
    QGlib::connect(pipeline->bus(), "message::error",
                   this, &VideoDecoderPrivate::onGstError);
    QGlib::connect(pipeline->bus(), "message::state-change",
                   this, &VideoDecoderPrivate::onStateChange);
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
void VideoDecoderPrivate::onInputData(QByteArray data)
{
    // Extract the real timestamp from the received data.
    const elapse::TimeStamp time = data.right(16).toULongLong(nullptr, 16);
    {
        QMutexLocker lock(&frameTimesLock);

        // Sanity check. This occasionally happens and I'm not sure why...
        if (!frameTimes.isEmpty() && time < frameTimes.last()) {
            qxtLog->warning("VideoDecoder: time went backwards!");
            qxtLog->debug("prev =", elapse::time::format(frameTimes.last()),
                          "this =", elapse::time::format(time));
        }

        // Store the real timestamp if it's not already stored.
        if (frameTimes.isEmpty() || frameTimes.last() != time)
            frameTimes.enqueue(time);
    }

    // Push the data into the decoder pipeline.
    data.chop(16);
    appsrc.pushBuffer(gstBufferFromBytes(data, CopyMethod::Deep));
}

/*!
 * Called when the decoder pipeline has decoded a frame of video. Pulls the
 * frame out of the pipeline, wraps it in a VideoSample, and emits the
 * newSample() signal. Called from an internal GStreamer thread.
 */
void VideoDecoderPrivate::onFrameDecoded()
{
    Q_Q(VideoDecoder);

    QGst::BufferPtr buff = appsink.pullBuffer();
    if (!buff)
        return;

    // Retrieve the real timestamp for this frame
    elapse::TimeStamp timestamp;
    {
        QMutexLocker lock(&frameTimesLock);
        Q_ASSERT(!frameTimes.isEmpty());
        timestamp = frameTimes.dequeue();
    }

    auto frame = elapse::VideoSample::createSubClass<GstVideoSample>(buff, timestamp);
    emit q->newSample(frame);
}

/*!
 * Construct a GstVideoSample which wraps the given \a buffer and has the
 * given \a timestamp.
 *
 * The VideoSample::data points directly to the QGst::Buffer::data() to
 * avoid an unnecessary copy.
 */
GstVideoSample::GstVideoSample(QGst::BufferPtr buffer, elapse::TimeStamp ts) :
    buff(buffer)
{
    auto caps = buff->caps()->internalStructure(0);

    timestamp = ts;
    w = caps->value("width").toInt();
    h = caps->value("height").toInt();
    data = QByteArray::fromRawData((const char*)buff->data(), buff->size());
}

/*!
 * Called when an error occurs in the GStreamer pipeline. Extracts the error
 * message, emits it as an error() signal, and stops the GStreamer pipeline.
 */
void VideoDecoderPrivate::onGstError(const QGst::MessagePtr &msg)
{
    Q_Q(VideoDecoder);
    auto err = msg.staticCast<QGst::ErrorMessage>();

    QString message("VideoDecoder: error from %1: %2");
    message = message.arg(err->source()->name(), err->error().message());
    qxtLog->error(message);
    emit q->error(message);

    pipeline->setState(QGst::StateNull);
}

/*!
 * Inspect the negotiated caps of the appsink once playback has started
 * and use this information to configure the video widget.
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
        if (displaysink) {
            displaysink->setVideoSink(pipeline->getElementByName("displaysink"));
            displaysink->setMinimumSize(videoSize);
        }
    }
}


/*!
 * Create a new VideoDecoder.
 *
 * Internally, the VideoDecoder uses a QGst::Pipeline to decode the video
 * stream.
 */
VideoDecoder::VideoDecoder() :
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
    d->onInputData(data);
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
        d->displaysink->setMinimumSize(100, 100);
        d->displaysink->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        // TODO: the displaysink shouldn't be in the gst pipeline at all
        // unless getWidget() has been called. If it is, it will display the
        // video in a window of its own.
    }
    return d->displaysink;
}

/*!
 * Prepare the VideoDecoder to accept data.
 */
void VideoDecoder::start()
{
    Q_D(VideoDecoder);
    {
        QMutexLocker lock(&d->frameTimesLock);
        d->frameTimes.clear();
    }
    d->pipeline->setState(QGst::StatePlaying);
}

/*!
 * Stop the VideoDecoder.
 */
void VideoDecoder::stop()
{
    Q_D(VideoDecoder);
    d->pipeline->setState(QGst::StateNull);
}

#include "videodecoder.moc" // because VideoDecoderPrivate inherits from QObject
