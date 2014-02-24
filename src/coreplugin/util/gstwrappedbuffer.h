#ifndef GSTWRAPPEDBUFFER_H
#define GSTWRAPPEDBUFFER_H

#include <QGst/Buffer>

/*!
 * \file
 * Supplementary functions for QGst.
 */

enum class CopyMethod { Shallow, Deep };

QGst::BufferPtr gstBufferFromBytes(const QByteArray &bytes, CopyMethod copy);

#endif // GSTWRAPPEDBUFFER_H
