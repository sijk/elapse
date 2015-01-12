#include <QDataStream>
#include <QSlider>
#include <QLabel>
#include <QLayout>
#include <QCheckBox>
#include <QPointer>
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
    uint nChannels;

    quint32 prevSeqnum;
    double toMicroVolts(double value) const;
    void checkSequenceNumber(const EegSample &sample);

    QPointer<QWidget> widgetContainer;
    QSlider *spacingSlider;
    QLabel *spacingValue;
    QCheckBox *demean;
    widgets::StripChart *stripChart;

    void createStripChart();
    void plotData(const EegSample &sample);
};


EegDecoderPrivate::EegDecoderPrivate() :
    vref(0),
    nChannels(8),
    prevSeqnum(0)
{
}

/*!
 * \return the \a reading converted to microvolts, given the current vref().
 */
double EegDecoderPrivate::toMicroVolts(double reading) const
{
    return reading * vref / ((1 << 23) - 1);
}

/*!
 * Check whether the current \a sample has a sequence number exactly one greater
 * than that of the previous sample, and log a warning message if it's not.
 */
void EegDecoderPrivate::checkSequenceNumber(const EegSample &sample)
{
    int dropped = sample.seqnum - prevSeqnum - 1;
    if (dropped)
        qxtLog->debug(dropped, "dropped samples");

    prevSeqnum = sample.seqnum;
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
    spacingLabel->setText("Zoom:");
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

    demean = new QCheckBox(widgetContainer);
    demean->setText("De-mean");
    spacingLayout->addSpacing(10);
    spacingLayout->addWidget(demean);

    layout->addLayout(spacingLayout);

    QObject::connect(spacingSlider, SIGNAL(valueChanged(int)),
                     spacingValue, SLOT(setNum(int)));
    QObject::connect(spacingSlider, SIGNAL(valueChanged(int)),
                     stripChart, SLOT(setSpacing(int)));
    QObject::connect(demean, SIGNAL(toggled(bool)),
                     stripChart, SLOT(setDemean(bool)));

    spacingSlider->setValue(1e3);
    demean->setChecked(stripChart->demean());
}

/*!
 * Append the data from the given \a sample to the widgets::StripChart.
 */
void EegDecoderPrivate::plotData(const EegSample &sample)
{
    stripChart->appendData(sample.values);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*!
 * Construct a new EegDecoder.
 */
EegDecoder::EegDecoder() :
    d_ptr(new EegDecoderPrivate)
{
}

EegDecoder::~EegDecoder() { }

/*!
 * Configure vref and nChannels to match the given hardware \a config.
 */
void EegDecoder::configure(QMap<QString, QVariantMap> config)
{
    Q_D(EegDecoder);

    d->nChannels = config["eeg"]["nChannels"].toUInt();
    d->vref = config["eeg"]["vref"].toDouble();

    if (d->stripChart)
        d->stripChart->setNStrips(d->nChannels);
}

/*!
 * Decode the given \a data and emit data::EegSample%s.
 */
void EegDecoder::onData(QByteArray data)
{
    Q_D(EegDecoder);
    BigEndian24 be24;
    qint32 status;
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

        d->plotData(*sample);
        d->checkSequenceNumber(*sample);
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
