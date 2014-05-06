#include "elapse/elements/featurextractor.h"
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
 * Create a BaseFeatureExtractor as a child of the given \a parent.
 */
elapse::BaseFeatureExtractor::BaseFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent),
    d_ptr(new BaseFeatureExtractorPrivate)
{
}

elapse::BaseFeatureExtractor::~BaseFeatureExtractor()
{
    delete d_ptr;
}

void elapse::BaseFeatureExtractor::setStartTime(quint64 timestamp)
{
    Q_D(BaseFeatureExtractor);
    reset();
    d->windowStart = timestamp;
    d->signalType = BaseFeatureExtractorPrivate::findSignalType(this);
}

void elapse::BaseFeatureExtractor::setWindowLength(uint ms)
{
    Q_D(BaseFeatureExtractor);
    d->windowLength = ms * 1e6;
}

void elapse::BaseFeatureExtractor::setWindowStep(uint ms)
{
    Q_D(BaseFeatureExtractor);
    d->windowStep = ms * 1e6;
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

    quint64 windowEnd = d->windowStart + d->windowLength;
    quint64 nextWindowStart = d->windowStart;
    quint64 nextWindowEnd;
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
    removeDataBefore(std::numeric_limits<quint64>::max());
}

