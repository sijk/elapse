#include <QQueue>
#include <QxtLogger>
#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappsink.h>
#include "sampletypes.h"
#include "videodecoder.h"


#define SRC_CAPS \
    "application/x-rtp, media=(string)video, "\
    "clock-rate=(int)90000, encoding-name=(string)H264, "\
    "sprop-parameter-sets=(string)\"Z0KAHukFD5CAAAH0AAB1MAIA\\,aM48gAA\\=\", "\
    "payload=(int)96"

#define PIPELINE \
    "appsrc name=src ! rtph264depay ! video/x-h264,framerate=60/1 ! " \
    "avdec_h264 ! appsink name=sink"

// TODO: Use an rtpjitterbuffer?


/*!
 * \brief The GstVideoSample struct makes a GstSample look like a VideoSample.
 */

struct GstVideoSample : VideoSample
{
    GstVideoSample(GstSample *sample);
    ~GstVideoSample();

private:
    GstBuffer *buff;
    GstMapInfo map;
};


/*!
 * \brief The VideoDecoderPrivate class hides the implementation details of the
 * VideoDecoder.
 *
 * It manages the GStreamer pipeline that does the actual video decoding.
 */

class VideoDecoderPrivate
{
public:
    VideoDecoderPrivate(VideoDecoder *q);
    ~VideoDecoderPrivate();

    GstElement *pipeline;
    GstAppSrc *appsrc;
    GstAppSink *appsink;
    GstBus *bus;
    QQueue<QByteArray> datastore;

    void onData(QByteArray data);
    static void deleteData(VideoDecoderPrivate *self);
    static GstFlowReturn onFrameDecoded(GstAppSink *sink, VideoDecoderPrivate *self);
    static void onVideoError(GstBus *bus, GstMessage *msg, VideoDecoderPrivate *self);

    VideoDecoder * const q_ptr;
    Q_DECLARE_PUBLIC(VideoDecoder)
};


/*!
 * Create the GStreamer pipeline which will do the actual video decoding. Also
 * starts the pipeline ready for input.
 */
VideoDecoderPrivate::VideoDecoderPrivate(VideoDecoder *q) :
    q_ptr(q)
{
    if (!gst_is_initialized()) {
        int argc = 0;
        gst_init(&argc, nullptr);
    }

    // Create the pipeline
    GError *gerror = nullptr;
    pipeline = gst_parse_launch(PIPELINE, &gerror);
    if (gerror) {
        qxtLog->error(gerror->message);
        g_clear_error(&gerror);
        if (pipeline)
            gst_object_unref(pipeline);
        pipeline = nullptr;
        return;
    }

    // Store references to the appsrc/sink
    appsrc = GST_APP_SRC(gst_bin_get_by_name(GST_BIN(pipeline), "src"));
    appsink = GST_APP_SINK(gst_bin_get_by_name(GST_BIN(pipeline), "sink"));

    // Configure the appsrc
    gst_app_src_set_stream_type(appsrc, GST_APP_STREAM_TYPE_STREAM);
    GstCaps *caps = gst_caps_from_string(SRC_CAPS);
    g_object_set(appsrc, "caps", caps,
                         "format", GST_FORMAT_TIME,
                         "is-live", true,
                         "do-timestamp", true,
                         NULL);
    gst_caps_unref(caps);

    // Configure the appsink
    g_object_set(appsink, "emit-signals", true, "sync", false, NULL);
    g_signal_connect(appsink, "new-sample", G_CALLBACK(onFrameDecoded), this);

    // Listen for error messages from the pipeline
    bus = gst_element_get_bus(pipeline);
    gst_bus_add_signal_watch(bus);
    g_signal_connect(bus, "message::error", G_CALLBACK(onVideoError), this);

    // Start the pipeline
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

/*!
 * Stop the decoding pipeline.
 */
VideoDecoderPrivate::~VideoDecoderPrivate()
{
    g_signal_handlers_disconnect_by_data(appsink, this);
    g_signal_handlers_disconnect_by_data(bus, this);
    gst_bus_remove_signal_watch(bus);
    g_object_unref(bus);

    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
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

    // Create a GstBuffer pointing to the given data
    GstBuffer *buff = gst_buffer_new_wrapped_full(GST_MEMORY_FLAG_READONLY,
                                                  (gpointer) data.data(),
                                                  data.size(), 0, data.size(),
                                                  this,
                                                  (GDestroyNotify) deleteData);
    // Push the buffer into the pipeline
    gst_app_src_push_buffer(appsrc, buff);
}

/*!
 * Called when a GstBuffer is destroyed. Removes the oldest QByteArray from
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
GstFlowReturn VideoDecoderPrivate::onFrameDecoded(GstAppSink *sink,
                                                  VideoDecoderPrivate *self)
{
    // Can't use Q_Q() because this is a static method
    VideoDecoder * const q = self->q_func();

    // Pull the decoded buffer from the appsink
    GstSample *sample = gst_app_sink_pull_sample(sink);
    if (!sample)
        return GST_FLOW_ERROR;

    // Wrap it up in a VideoSample and send it on its way
    auto frame = new GstVideoSample(sample);
    emit q->newSample(SamplePtr(frame));

    gst_sample_unref(sample);
    return GST_FLOW_OK;
}

/*!
 * Construct a GstVideoSample which wraps the given \a sample.
 *
 * The GstBuffer contained in the given GstSample is extracted and kept alive
 * until this GstVideoSample is destroyed.
 */
GstVideoSample::GstVideoSample(GstSample *sample)
{
    buff = gst_sample_get_buffer(sample);
    gst_buffer_ref(buff);

    // Get frame timestamp
    timestamp = buff->dts;

    // Get frame dimensions
    GstCaps *caps = gst_sample_get_caps(sample);
    GstStructure *capstruct = gst_caps_get_structure(caps, 0);
    gst_structure_get_int(capstruct, "width", &w);
    gst_structure_get_int(capstruct, "height", &h);

    // Get pointer to frame data
    gst_buffer_map(buff, &map, GST_MAP_READ);
    data = QByteArray::fromRawData((const char*)map.data, map.size);
}

/*!
 * Destroy this GstVideoSample and the GstBuffer it contains.
 */
GstVideoSample::~GstVideoSample()
{
    gst_buffer_unmap(buff, &map);
    gst_buffer_unref(buff);
}

/*!
 * Called when an error occurs in the GStreamer pipeline. Extracts the error
 * message and emits it as an error() signal.
 */
void VideoDecoderPrivate::onVideoError(GstBus *bus, GstMessage *msg,
                                       VideoDecoderPrivate *self)
{
    Q_UNUSED(bus);
//    VideoDecoder * const q = self->q_func();
    GError *gerror;
    gchar *debugInfo;
    gst_message_parse_error(msg, &gerror, &debugInfo);

    QString message("VideoDecoder error from %1: %2");
    message = message.arg(GST_OBJECT_NAME(msg->src)).arg(gerror->message);
//    emit q->error(message);
    qxtLog->error(message);

    g_clear_error(&gerror);
    g_free(debugInfo);
    gst_element_set_state(self->pipeline, GST_STATE_NULL);
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
