#include <gtest/gtest.h>

#define private public
#include "util/bigendian24.h"
#undef private


struct StreamData { QByteArray input; char bytes[3]; };

class BigEndian24StreamTest : public testing::TestWithParam<StreamData> { };

TEST_P(BigEndian24StreamTest, CanReadFromStream)
{
    StreamData data = GetParam();
    QDataStream stream(data.input);
    BigEndian24 be24;

    stream >> be24;

    EXPECT_EQ(be24.bytes[0], data.bytes[0]);
    EXPECT_EQ(be24.bytes[1], data.bytes[1]);
    EXPECT_EQ(be24.bytes[2], data.bytes[2]);
}

INSTANTIATE_TEST_CASE_P(ReadFromStream, BigEndian24StreamTest,
                        testing::ValuesIn(QList<StreamData>({
    { QByteArray("\x00\x00\x00", 3), {'\x00', '\x00', '\x00'} },
    { QByteArray("\x00\x00\x01", 3), {'\x00', '\x00', '\x01'} },
    { QByteArray("\x7F\xFF\xFF", 3), {'\x7F', '\xFF', '\xFF'} },
    { QByteArray("\x80\x00\x00", 3), {'\x80', '\x00', '\x00'} },
    { QByteArray("\xFF\xFF\xFF", 3), {'\xFF', '\xFF', '\xFF'} },
})));



struct ConvertData { QByteArray input; qint32 output; };

class BigEndian24ConvertTest : public testing::TestWithParam<ConvertData> { };

TEST_P(BigEndian24ConvertTest, CanConvertToS32)
{
    ConvertData data = GetParam();
    QDataStream stream(data.input);
    BigEndian24 be24;

    stream >> be24;

    EXPECT_EQ(be24.to32bit(), data.output);
}

INSTANTIATE_TEST_CASE_P(ConvertFromStream, BigEndian24ConvertTest,
                        testing::ValuesIn(QList<ConvertData>({
    { QByteArray("\x7F\xFF\xFF", 3), qint32(8388607) },
    { QByteArray("\x00\x00\x01", 3), qint32(1) },
    { QByteArray("\x00\x00\x00", 3), qint32(0) },
    { QByteArray("\xFF\xFF\xFF", 3), qint32(-1) },
    { QByteArray("\x80\x00\x00", 3), qint32(-8388608) },
})));
