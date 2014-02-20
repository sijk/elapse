#include <gst/gst.h>
#include <QHash>
#include <QxtLogger>
#include "gstwrappedbuffer.h"

static void freeFunc(GstBuffer *buff);
static QHash<GstBuffer *, QByteArray> cache;

/*!
 * Create a new GStreamer buffer which points to the \a bytes in the given
 * \c QByteArray.
 *
 * Internally, the \c QByteArray is added to a cache to ensure that its
 * reference count does not drop to zero while the \c GstBuffer holds a
 * reference to its internal data. The \c QByteArray is removed from the
 * cache by a custom \c GstBuffer::free_func.
 *
 * This function is necessary because the QtGstreamer bindings don't provide
 * a way to create a \c QGst::Buffer from existing data.
 *
 * \return a \c QGst::BufferPtr to the new buffer.
 */
QGst::BufferPtr QGst::bufferFromBytes(const QByteArray &bytes)
{
    GstBuffer *buff = gst_buffer_new();
    gst_buffer_set_data(buff, (guint8*)bytes.data(), bytes.size());

    GST_BUFFER_MALLOCDATA(buff) = (guint8*)buff;
    GST_BUFFER_FREE_FUNC(buff) = (GFreeFunc)freeFunc;

    if (cache.contains(buff))
        qxtLog->debug() << qulonglong(buff) << "already in the cache!";

    cache.insert(buff, bytes);

    return QGst::BufferPtr::wrap(buff, false);
}

/*!
 * Remove the data associated with the given buffer from the cache. Called
 * when the buffer is freed.
 */
void freeFunc(GstBuffer *buff)
{
    if (!cache.contains(buff))
        qxtLog->debug() << qulonglong(buff) << "not found in cache!";

    cache.remove(buff);
}
