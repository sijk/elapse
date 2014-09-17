#include <QDataStream>
#include <QSlider>
#include <QLabel>
#include <QLayout>
#include <QxtLogger>
#include <elapse/datatypes.h>
#include "util/bigendian24.h"
#include "stripchart.h"
#include "eegdecoder.h"

#define CHANNELS_PER_CHIP   8

namespace elapse { namespace coreplugin {

using elapse::data::EegSample;


class EegDecoderPrivate
{
public:
    EegDecoderPrivate();

    double vref;
    quint8 gain;
    uint nChannels;

    double toMicroVolts(double value) const;
    static void checkSequenceNumber(EegSample::const_ptr sample);

    QWidget *widgetContainer;
    QSlider *spacingSlider;
    QLabel *spacingValue;
    widgets::StripChart *stripChart;

    void createStripChart();
    void plotData(EegSample::const_ptr sample);
};


EegDecoderPrivate::EegDecoderPrivate() :
    vref(0),
    gain(1),
    nChannels(8),
    widgetContainer(nullptr)
{
}

/*!
 * \return the \a reading converted to microvolts, given the current gain()
 * and vref().
 */
double EegDecoderPrivate::toMicroVolts(double reading) const
{
    return reading / gain * vref / ((1 << 23) - 1);
}

/*!
 * Check whether the current \a sample has a sequence number exactly one greater
 * than that of the previous sample, and log a warning message if it's not.
 */
void EegDecoderPrivate::checkSequenceNumber(EegSample::const_ptr sample)
{
    static quint32 prev_seqnum = 0;

    int dropped = sample->seqnum - prev_seqnum - 1;
    if (dropped)
        qxtLog->debug(dropped, "dropped samples");

    prev_seqnum = sample->seqnum;
}

/*!
 * Create a widgets::StripChart for displaying the EEG, along with a slider
 * to adjust the scale.
 */
void EegDecoderPrivate::createStripChart()
{
    Q_ASSERT(!widgetContainer);
    widgetContainer = new QWidget;

    auto layout = new QVBoxLayout(widgetContainer);
    layout->setMargin(0);
    layout->setSpacing(0);

    stripChart = new widgets::StripChart(widgetContainer);
    stripChart->setNStrips(nChannels);
    stripChart->setNSamples(1000);
    layout->addWidget(stripChart, 1);

    auto spacingLayout = new QHBoxLayout;
    spacingLayout->setContentsMargins(10, 0, 10, 10);
    spacingLayout->setSpacing(6);

    auto spacingLabel = new QLabel(widgetContainer);
    spacingLabel->setText("Amplitude:");
    spacingLayout->addWidget(spacingLabel);

    spacingSlider = new QSlider(widgetContainer);
    spacingSlider->setOrientation(Qt::Horizontal);
    spacingSlider->setMinimum(1);
    spacingSlider->setMaximum(1e5);
    spacingSlider->setSingleStep(100);
    spacingSlider->setPageStep(1000);
    spacingLayout->addWidget(spacingSlider);

    spacingValue = new QLabel(widgetContainer);
    spacingLayout->addWidget(spacingValue);

    auto units = new QLabel(widgetContainer);
    units->setText("uV");
    spacingLayout->addWidget(units);

    layout->addLayout(spacingLayout);

    QObject::connect(spacingSlider, SIGNAL(valueChanged(int)),
                     spacingValue, SLOT(setNum(int)));
    QObject::connect(spacingSlider, SIGNAL(valueChanged(int)),
                     stripChart, SLOT(setSpacing(int)));

    spacingSlider->setValue(6e3);
}

/*!
 * Append the data from the given \a sample to the widgets::StripChart.
 */
void EegDecoderPrivate::plotData(EegSample::const_ptr sample)
{
    stripChart->appendData(sample->values);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*!
 * Construct a new EegDecoder.
 */
EegDecoder::EegDecoder() :
    d_ptr(new EegDecoderPrivate)
{
}

/*!
 * Destroy this EegDecoder.
 */
EegDecoder::~EegDecoder()
{
    delete d_ptr;
}

/*!
 * Configure gain, vref, and nChannels to match the given hardware \a config.
 */
void EegDecoder::configure(QMap<QString, QVariantMap> config)
{
    setNChannels(config["eeg"]["nChannels"].toUInt());
    setVref(config["eeg"]["vref"].toDouble());
    setGain(config["eeg/channel/0"]["gain"].toUInt());
}

/*!
 * The device's current gain setting for all channels.
 */
quint8 EegDecoder::gain() const
{
    Q_D(const EegDecoder);
    return d->gain;
}

/*!
 * Set the device's current \a gain setting for all channels.
 */
void EegDecoder::setGain(quint8 gain)
{
    Q_D(EegDecoder);
    d->gain = gain;
}

/*!
 * The device's current reference voltage in microvolts.
 */
double EegDecoder::vref() const
{
    Q_D(const EegDecoder);
    return d->vref;
}

/*!
 * Set the device's current reference voltage to \a vref in microvolts.
 */
void EegDecoder::setVref(double vref)
{
    Q_D(EegDecoder);
    d->vref = vref;
}

/*!
 * The number of EEG channels that the device has.
 */
uint EegDecoder::nChannels() const
{
    Q_D(const EegDecoder);
    return d->nChannels;
}

/*!
 * Set the number of EEG channels that the device has to \a nChannels.
 */
void EegDecoder::setNChannels(uint nChannels)
{
    Q_D(EegDecoder);
    d->nChannels = nChannels;
    if (d->stripChart)
        d->stripChart->setNStrips(nChannels);
}

/*!
 * Decode the given \a data and emit data::EegSample%s.
 */
void EegDecoder::onData(QByteArray data)
{
    Q_D(EegDecoder);
    BigEndian24 be24;
    quint32 status;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd()) {
        auto sample = EegSample::create();

        stream >> sample->seqnum;
        stream >> sample->timestamp;

        sample->values.reserve(d->nChannels);

        for (uint chip = 0; chip < d->nChannels / CHANNELS_PER_CHIP; chip++) {
            stream >> be24;
            status = be24.to32bit();
            quint8 loffStatP = (status >> 12) & 0xFF;
            sample->leadOff |= loffStatP << (CHANNELS_PER_CHIP * chip);

            for (uint channel = 0; channel < CHANNELS_PER_CHIP; channel++) {
                stream >> be24;
                sample->values.push_back(d->toMicroVolts(be24.to32bit()));
            }
        }

        d->plotData(sample);
        d->checkSequenceNumber(sample);
        emit newSample(sample);
    }
}

/*!
 * \return a widgets::StripChart displaying the measured EEG data, along with
 * associated widgets to adjust the plot scale.
 */
QWidget *EegDecoder::getWidget()
{
    Q_D(EegDecoder);
    if (!d->widgetContainer)
        d->createStripChart();
    return d->widgetContainer;
}

}} // namespace elapse::coreplugin
