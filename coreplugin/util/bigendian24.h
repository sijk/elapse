/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef BIGENDIAN24_H
#define BIGENDIAN24_H

#include <QDataStream>

/*!
 * \brief The BigEndian24 class parses 24-bit big-endian integers from a
 * QDataStream.
 *
 * \code
 * QDataStream stream(...);
 * BigEndian24 value24;
 * qint32 value32;
 *
 * stream >> value24;
 * value32 = value24.to32bit();
 * \endcode
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
