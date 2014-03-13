#include <QtTest>
#include "util/bigendian24.h"

class BigEndian24Test : public QObject
{
    Q_OBJECT

private slots:
    void canReadFromStream_data();
    void canReadFromStream();
    void canConvertToS32_data();
    void canConvertToS32();
};


void BigEndian24Test::canReadFromStream_data()
{
    QTest::addColumn<QByteArray>("bytes");
    QTest::addColumn<char>("b0");
    QTest::addColumn<char>("b1");
    QTest::addColumn<char>("b2");

    QTest::newRow("000000") << QByteArray("\x00\x00\x00", 3)
                            << char(0x00) << char(0x00) << char(0x00);
    QTest::newRow("000001") << QByteArray("\x00\x00\x01", 3)
                            << char(0x00) << char(0x00) << char(0x01);
    QTest::newRow("7FFFFF") << QByteArray("\x7F\xFF\xFF", 3)
                            << char(0x7F) << char(0xFF) << char(0xFF);
    QTest::newRow("800000") << QByteArray("\x80\x00\x00", 3)
                            << char(0x80) << char(0x00) << char(0x00);
    QTest::newRow("FFFFFF") << QByteArray("\xFF\xFF\xFF", 3)
                            << char(0xFF) << char(0xFF) << char(0xFF);
}

void BigEndian24Test::canReadFromStream()
{
    QFETCH(QByteArray, bytes);
    QDataStream stream(bytes);

    BigEndian24 be24;
    stream >> be24;

    QTEST(be24.bytes[0], "b0");
    QTEST(be24.bytes[1], "b1");
    QTEST(be24.bytes[2], "b2");
}

void BigEndian24Test::canConvertToS32_data()
{
    QTest::addColumn<QByteArray>("bytes");
    QTest::addColumn<qint32>("value");

    QTest::newRow("7FFFFF") << QByteArray("\x7F\xFF\xFF", 3) << qint32(8388607);
    QTest::newRow("000001") << QByteArray("\x00\x00\x01", 3) << qint32(1);
    QTest::newRow("000000") << QByteArray("\x00\x00\x00", 3) << qint32(0);
    QTest::newRow("FFFFFF") << QByteArray("\xFF\xFF\xFF", 3) << qint32(-1);
    QTest::newRow("800000") << QByteArray("\x80\x00\x00", 3) << qint32(-8388608);
}

void BigEndian24Test::canConvertToS32()
{
    QFETCH(QByteArray, bytes);
    QDataStream stream(bytes);

    BigEndian24 be24;
    stream >> be24;

    QTEST(be24.to32bit(), "value");
}


QTEST_APPLESS_MAIN(BigEndian24Test)
#include "tst_bigendian24.moc"
