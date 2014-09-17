#include "elapse/elements/featurextractor.h"
#include "elapse/elements/simple/eegfeaturextractor.h"
#include "elapse/timestamps.h"
#include "featurextractor_p.h"

using namespace elapse::data;

namespace elapse { namespace elements {

BaseFeatureExtractorPrivate::BaseFeatureExtractorPrivate() :
    windowStart(0),
    signalType(Signal::INVALID)
{
}

/*!
 * \return the Signal::Type this FeatureExtractor works with, as defined
 * by the "SignalType" class info field.
 */
Signal::Type BaseFeatureExtractorPrivate::findSignalType(const BaseFeatureExtractor *q)
{
    const int index = q->metaObject()->indexOfClassInfo("SignalType");
    const char *info = q->metaObject()->classInfo(index).value();
    return Signal::fromString(info);
}

BaseFeatureExtractorPrivate *BaseFeatureExtractorPrivate::expose(BaseFeatureExtractor *q)
{
    return q->d_func();
}


/*!
 * Create a BaseFeatureExtractor.
 */
BaseFeatureExtractor::BaseFeatureExtractor() :
    d_ptr(new BaseFeatureExtractorPrivate)
{
}

BaseFeatureExtractor::~BaseFeatureExtractor()
{
    delete d_ptr;
}

void BaseFeatureExtractor::setStartTime(time::Point timestamp)
{
    Q_D(BaseFeatureExtractor);
    reset();
    d->windowStart = timestamp;
    d->signalType = signalType();
}

void BaseFeatureExtractor::setWindowLength(uint length)
{
    Q_D(BaseFeatureExtractor);
    d->windowLength = time::from_ms(length);
}

void BaseFeatureExtractor::setWindowStep(uint step)
{
    Q_D(BaseFeatureExtractor);
    d->windowStep = time::from_ms(step);
}

/*!
 * Handle the given \a sample. This method takes care of updating the
 * window as necessary and delegates the actual feature extraction to
 * the protected methods.
 */
void BaseFeatureExtractor::onSample(SamplePtr sample)
{
    Q_D(BaseFeatureExtractor);

    if (d->windowStart == 0)
        return;

    Q_ASSERT(d->signalType != Signal::INVALID);

    if (sample->timestamp < d->windowStart) {
        return;
    }

    time::Point windowEnd = d->windowStart + d->windowLength;
    time::Point nextWindowStart = d->windowStart;
    time::Point nextWindowEnd;
    do {
        nextWindowStart += d->windowStep;
        nextWindowEnd = nextWindowStart + d->windowLength;
    } while (sample->timestamp >= nextWindowEnd);

    if (sample->timestamp >= windowEnd) {
        FeatureVector featureVector(d->signalType, d->windowStart);
        featureVector.features = features();
        emit newFeatures(featureVector);

        removeDataBefore(nextWindowStart);
        d->windowStart = nextWindowStart;
    }

    analyseSample(sample);
}

void BaseFeatureExtractor::reset()
{
    removeDataBefore(std::numeric_limits<time::Point>::max());
}

Signal::Type BaseFeatureExtractor::signalType() const
{
    return BaseFeatureExtractorPrivate::findSignalType(this);
}


/*! Store the sampleRate for later. */
void SimpleEegFeatureExtractor::configure(QMap<QString, QVariantMap> config)
{
    sampFreq = config["eeg"]["sampleRate"].toUInt();
}

/*! Save the \a sample for later. */
void SimpleEegFeatureExtractor::analyseSample(SamplePtr sample)
{
    auto eeg = EegSample::staticCastFrom(sample);
    samples[eeg->timestamp] = eeg;
}

/*!
 * Create an Eigen matrix from the EEG samples in the current window and pass
 * it to extractFeatures().
 */
std::vector<double> SimpleEegFeatureExtractor::features()
{
    uint nSamples = samples.size();
    Q_ASSERT(nSamples > 0);
    uint nChannels = samples.cbegin()->second->values.size();

    // Eigen's default storage order is column-major, so store EEG data as
    // one column per channel.
    Eigen::MatrixXd data(nSamples, nChannels);

    uint r = 0;
    for (const auto &sample : samples) {
        const data::EegSample *eeg = sample.second.get();
        Eigen::Map<const Eigen::RowVectorXd> row(eeg->values.data(), nChannels);
        data.row(r++) = row;
    }

    return extractFeatures(data, sampFreq);
}

void SimpleEegFeatureExtractor::removeDataBefore(time::Point time)
{
    samples.removeValuesBefore(time);
}

}} // namespace elapse::elements
