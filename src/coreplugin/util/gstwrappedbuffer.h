#ifndef GSTWRAPPEDBUFFER_H
#define GSTWRAPPEDBUFFER_H

#include <QGst/Buffer>

/*!
 * \brief Local additions to QtGstreamer.
 */
namespace QGst {

QGst::BufferPtr bufferFromBytes(const QByteArray &bytes);

}

#endif // GSTWRAPPEDBUFFER_H
