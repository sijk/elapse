#include "elapse/elements/featurextractor.h"
#include "elapse/timestamps.h"
#include "featurextractor_p.h"


elapse::BaseFeatureExtractorPrivate::BaseFeatureExtractorPrivate() :
    windowStart(0),
    signalType(Signal::INVALID)
{
}

/*!
 * \return the Signal::Type this FeatureExtractor works with, as defined
 * by the "SignalType" class info field.
 */
elapse::Signal::Type elapse::BaseFeatureExtractorPrivate::findSignalType(BaseFeatureExtractor *q)
{
    const int index = q->metaObject()->indexOfClassInfo("SignalType");
    const char *info = q->metaObject()->classInfo(index).value();
    return Signal::fromString(info);
}

elapse::BaseFeatureExtractorPrivate *elapse::BaseFeatureExtractorPrivate::expose(BaseFeatureExtractor *q)
{
    return q->d_func();
}


/*!
 * Create a BaseFeatureExtractor.
 */
elapse::BaseFeatureExtractor::BaseFeatureExtractor() :
    d_ptr(new BaseFeatureExtractorPrivate)
{
}

elapse::BaseFeatureExtractor::~BaseFeatureExtractor()
{
    delete d_ptr;
}

void elapse::BaseFeatureExtractor::setStartTime(TimeStamp timestamp)
{
    Q_D(BaseFeatureExtractor);
    reset();
    d->windowStart = timestamp;
    d->signalType = BaseFeatureExtractorPrivate::findSignalType(this);
}

void elapse::BaseFeatureExtractor::setWindowLength(uint length)
{
    Q_D(BaseFeatureExtractor);
    d->windowLength = time::from_ms(length);
}

void elapse::BaseFeatureExtractor::setWindowStep(uint step)
{
    Q_D(BaseFeatureExtractor);
    d->windowStep = time::from_ms(step);
}

/*!
 * Handle the given \a sample. This method takes care of updating the
 * window as necessary and delegates the actual feature extraction to
 * the protected methods.
 */
void elapse::BaseFeatureExtractor::onSample(elapse::SamplePtr sample)
{
    Q_D(BaseFeatureExtractor);

    if (d->windowStart == 0)
        return;

    Q_ASSERT(d->signalType != Signal::INVALID);

    if (sample->timestamp < d->windowStart) {
        return;
    }

    TimeStamp windowEnd = d->windowStart + d->windowLength;
    TimeStamp nextWindowStart = d->windowStart;
    TimeStamp nextWindowEnd;
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

void elapse::BaseFeatureExtractor::reset()
{
    removeDataBefore(std::numeric_limits<TimeStamp>::max());
}

