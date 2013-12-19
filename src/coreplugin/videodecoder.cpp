#include <QQueue>
#include <QxtLogger>
#include <QGst/Init>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Pipeline>
#include <QGst/Element>
#include <QGst/Utils/ApplicationSource>
#include <QGst/Utils/ApplicationSink>
#include <QGst/Bus>
#include <QGst/Parse>
#include <QGst/Message>
#include <gst/gst.h>
#include "sampletypes.h"
#include "videodecoder.h"


#define SRC_CAPS \
    "application/x-rtp, media=(string)video, "\
    "clock-rate=(int)90000, encoding-name=(string)H264, "\
    "sprop-parameter-sets=(string)\"Z0KAHukFD5CAAAH0AAB1MAIA\\,aM48gAA\\=\", "\
    "payload=(int)96"

#define PIPELINE \
    "appsrc name=src ! rtph264depay ! video/x-h264,framerate=60/1 ! " \
    "ffdec_h264 ! appsink name=sink"

// TODO: Use an rtpjitterbuffer?


/*!
 * \brief The GstVideoSample struct makes a QGst::Buffer look like a VideoSample.
 *
 * It keeps a reference to the QGst::Buffer in order to keep it alive until
 * the VideoSample is destroyed.
 */

struct GstVideoSample : VideoSample
{
    GstVideoSample(QGst::BufferPtr buffer);

private:
    QGst::BufferPtr buff;
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
    QGst::Utils::ApplicationSink appsink;
    QQueue<QByteArray> datastore;

    void onData(QByteArray data);
    static void deleteData(VideoDecoderPrivate *self);
    QGst::FlowReturn onFrameDecoded();
    void onVideoError(const QGst::MessagePtr &msg);
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
        return;
    }

    appsrc.setElement(pipeline->getElementByName("src"));
    appsrc.setCaps(QGst::Caps::fromString(SRC_CAPS));
    appsrc.setStreamType(QGst::AppStreamTypeStream);
    appsrc.setFormat(QGst::FormatTime);
    appsrc.setLive(true);
    appsrc.element()->setProperty("do-timestamp", true);

    appsink.setElement(pipeline->getElementByName("sink"));
    appsink.element()->setProperty("sync", false);
    appsink.element()->setProperty("emit-signals", true);
    QGlib::connect(appsink.element(), "new-buffer",
                   this, &VideoDecoderPrivate::onFrameDecoded);

    pipeline->bus()->addSignalWatch();
    QGlib::connect(pipeline->bus(), "message::error",
                   this, &VideoDecoderPrivate::onVideoError);

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
 * GstBuffer and pushes it into the pipeline.
 *
 * To avoid copying, the GstBuffer points to the data in the given QByteArray.
 * We therefore need to keep a reference to the QByteArray so that it doesn't
 * get destroyed before the GstBuffer is finished with it's data. We push the
 * array into a queue from which it automatically gets removed when the
 * GstBuffer is destroyed.
 *
 * \see VideoDecoderPrivate::deleteData()
 */
void VideoDecoderPrivate::onData(QByteArray data)
{
    // Store the QByteArray since we aren't going to copy the data into the
    // GstBuffer. Adding a QByteArray to a queue doesn't cause a deep copy
    // because it is implicitly shared.
    datastore.enqueue(data);

    // Unfortunately QtGStreamer doesn't expose the ability to create buffers
    // without allocating data; we have to revert to the C API.
    GstBuffer *buff = gst_buffer_new();
    gst_buffer_set_data(buff, (guint8*)data.data(), data.size());

    // Abuse the 'malloc_data' field to call our own cleanup function
    GST_BUFFER_MALLOCDATA(buff) = (guint8*)this;
    GST_BUFFER_FREE_FUNC(buff) = (GFreeFunc)&VideoDecoderPrivate::deleteData;

    // Push the buffer into the decoder pipeline
    QGst::BufferPtr buffp = QGst::BufferPtr::wrap(buff, false);

    appsrc.pushBuffer(buffp);
}

/*!
 * Called when a QGst::Buffer is destroyed. Removes the oldest QByteArray from
 * the queue.
 *
 * \see VideoDecoderPrivate::onData()
 */
void VideoDecoderPrivate::deleteData(VideoDecoderPrivate *self)
{
    self->datastore.dequeue();
}

/*!
 * Called when the decoder pipeline has decoded a frame of video. Pulls the
 * frame out of the pipeline, wraps it in a VideoSample, and emits the
 * newSample() signal.
 */
QGst::FlowReturn VideoDecoderPrivate::onFrameDecoded()
{
    Q_Q(VideoDecoder);

    QGst::BufferPtr buff = appsink.pullBuffer();
    if (!buff)
        return QGst::FlowError;

    auto frame = new GstVideoSample(buff);
    emit q->newSample(SamplePtr(frame));

    return QGst::FlowOk;
}

/*!
 * Construct a GstVideoSample which wraps the given \a buffer.
 */
GstVideoSample::GstVideoSample(QGst::BufferPtr buffer) :
    buff(buffer)
{
    auto caps = buff->caps()->internalStructure(0);

    timestamp = buff->timeStamp();
    w = caps->value("width").toInt();
    w = caps->value("height").toInt();
    data = QByteArray::fromRawData((const char*)buff->data(), buff->size());
}

/*!
 * Called when an error occurs in the GStreamer pipeline. Extracts the error
 * message and emits it as an error() signal.
 */
void VideoDecoderPrivate::onVideoError(const QGst::MessagePtr &msg)
{
//    Q_Q(VideoDecoder);
    auto err = msg.staticCast<QGst::ErrorMessage>();

    QString message("VideoDecoder error from %1: %2");
    message = message.arg(err->source()->name()).arg(err->error().message());
    qxtLog->error(message);
//    emit q->error(message);

    pipeline->setState(QGst::StateNull);
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

#include "videodecoder.moc" // because VideoDecoderPrivate inherits from QObject
