#ifndef BIGENDIAN24_H
#define BIGENDIAN24_H

#include <QDataStream>

/*
 * Helper class to parse 24-bit big-endian integers from a QDataStream.
 */

struct BigEndian24
{
    char bytes[3];
    inline qint32 to32bit() const;
};

qint32 BigEndian24::to32bit() const
{
    // Set the high 24 bits and then right shift to get correct sign extension
    return ((uchar(bytes[0]) << 24) |
            (uchar(bytes[1]) << 16) |
            (uchar(bytes[2]) << 8)) >> 8;
}

QDataStream &operator>>(QDataStream &stream, BigEndian24 &value)
{
    stream.readRawData(value.bytes, 3);
    return stream;
}

#endif // BIGENDIAN24_H
