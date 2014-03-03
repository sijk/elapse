#ifndef BIGENDIAN24_H
#define BIGENDIAN24_H

#include <QDataStream>

/*!
 * \brief The BigEndian24 class parses 24-bit big-endian integers from a
 * QDataStream.
 */

class BigEndian24
{
public:
    inline qint32 to32bit() const;

private:
    char bytes[3];
    friend QDataStream &operator>>(QDataStream &stream, BigEndian24 &value);
};

/*!
 * \return the value as a signed 32-bit integer.
 */
qint32 BigEndian24::to32bit() const
{
    // Set the high 24 bits and then right shift to get correct sign extension
    return ((uchar(bytes[0]) << 24) |
            (uchar(bytes[1]) << 16) |
            (uchar(bytes[2]) << 8)) >> 8;
}

/*!
 * Read a BigEndian24 value from a QDataStream.
 */
QDataStream &operator>>(QDataStream &stream, BigEndian24 &value)
{
    stream.readRawData(value.bytes, 3);
    return stream;
}

#endif // BIGENDIAN24_H
