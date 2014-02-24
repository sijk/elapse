#include <gst/gst.h>
#include <cstring>
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
QGst::BufferPtr gstBufferFromBytes_shallow(const QByteArray &bytes)
{
    GstBuffer *buff = gst_buffer_new();
    gst_buffer_set_data(buff, (guint8*)bytes.data(), bytes.size());

    GST_BUFFER_MALLOCDATA(buff) = (guint8*)buff;
    GST_BUFFER_FREE_FUNC(buff) = (GFreeFunc)freeFunc;

    Q_ASSERT(!cache.contains(buff));

    cache.insert(buff, bytes);
    auto gstBuff = QGst::BufferPtr::wrap(buff, false);

    Q_ASSERT(cache.contains(buff));
    return gstBuff;
}

/*!
 * Remove the data associated with the given buffer from the cache. Called
 * when the buffer is freed.
 */
void freeFunc(GstBuffer *buff)
{
    Q_ASSERT(cache.contains(buff));
    cache.remove(buff);
    Q_ASSERT(!cache.contains(buff));
}


/*!
 * Create a new GStreamer buffer with a copy of the given \bytes.
 *
 * \return a \c QGst::BufferPtr to the new buffer.
 */
QGst::BufferPtr gstBufferFromBytes_deep(const QByteArray &bytes)
{
    QGst::BufferPtr buff = QGst::Buffer::create(bytes.size());
    std::memcpy(buff->data(), bytes.constData(), bytes.size());
    return buff;
}


/*!
 * Create a new QGst::Buffer from the given \a bytes.
 *
 * - If \a copy is \c Deep, the contents of the \c QByteArray are copied
 *   into the newly-allocated buffer.
 * - If \a copy is \c Shallow, the buffer's data pointer will point to
 *   the contents of the QByteArray; i.e. the data won't be copied. In this
 *   case the QByteArray is added to an internal cache to ensure that it
 *   is not destroyed until the buffer is destroyed.
 *
 * \return a QGst::BufferPtr to the new buffer.
 */
QGst::BufferPtr gstBufferFromBytes(const QByteArray &bytes, CopyMethod copy)
{
    return (copy == CopyMethod::Deep) ? gstBufferFromBytes_deep(bytes)
                                      : gstBufferFromBytes_shallow(bytes);
}
