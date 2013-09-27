#include <QtTest>

#include <QDebug>
#include "eegdecoder.h"


class EegDecoderTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void canConvertReadingsToMicroVolts_data();
    void canConvertReadingsToMicroVolts();

private:
    EegDecoder *eegdec;
};


/* Helper class to get pointers to private methods. */
template<typename PrivMethodPtr, PrivMethodPtr value>
struct PrivateAccessor
{
    static PrivMethodPtr get() { return value; }
};


void EegDecoderTest::init()
{
    eegdec = new EegDecoder;
}

void EegDecoderTest::cleanup()
{
    delete eegdec;
}

void EegDecoderTest::canConvertReadingsToMicroVolts_data()
{
    QTest::addColumn<quint8>("gain");
    QTest::addColumn<double>("vref");
    QTest::addColumn<qint32>("reading");
    QTest::addColumn<double>("voltage");

    QList<quint8> gains{1, 24};
    QList<double> vrefs{4.5e6, 2.048e6};

    foreach (quint8 gain, gains) {
        foreach (double vref, vrefs) {
            double limit = vref / gain;

            auto name = [&](const QString &name) {
                return QString("%1 @ %2x%3").arg(name).arg(gain).arg(vref).toLatin1();
            };

            // See p25 of the ADS1299 datasheet
            QTest::newRow(name("0x7FFFFF")) << gain << vref << qint32(0x007FFFFF) << limit;
            QTest::newRow(name("0x000001")) << gain << vref << qint32(0x00000001) << limit / ((1<<23)-1);
            QTest::newRow(name("0x000000")) << gain << vref << qint32(0x00000000) << 0.0;
            QTest::newRow(name("0xFFFFFF")) << gain << vref << qint32(0xFFFFFFFF) << -limit / ((1<<23)-1);
            QTest::newRow(name("0x800000")) << gain << vref << qint32(0xFF800000) << -limit * (1<<23)/((1<<23)-1);
        }
    }
}

void EegDecoderTest::canConvertReadingsToMicroVolts()
{
    // Get a pointer to the private toMicroVolts method
    auto toMicroVolts = PrivateAccessor<double(EegDecoder::*)(double)const,
                                        &EegDecoder::toMicroVolts>::get();

    QFETCH(quint8, gain);
    QFETCH(double, vref);
    QFETCH(qint32, reading);
    QFETCH(double, voltage);

    eegdec->setProperty("gain", gain);
    eegdec->setProperty("vref", vref);
    QCOMPARE((eegdec->*toMicroVolts)(reading), voltage);
}


QTEST_GUILESS_MAIN(EegDecoderTest)
#include "tst_eegdecoder.moc"
