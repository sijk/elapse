#include "elapse/elements/featurextractor.h"


/*!
 * Create a BaseFeatureExtractor as a child of the given \a parent.
 */
elapse::BaseFeatureExtractor::BaseFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent),
    windowStart(0),
    signalType(Signal::INVALID)
{
}

void elapse::BaseFeatureExtractor::setStartTime(quint64 timestamp)
{
    reset();
    windowStart = timestamp;
    signalType = findSignalType();
}

void elapse::BaseFeatureExtractor::setWindowLength(uint ms)
{
    windowLength = ms;
}

void elapse::BaseFeatureExtractor::setWindowStep(uint ms)
{
    windowStep = ms;
}

/*!
 * Handle the given \a sample. This method takes care of updating the
 * window as necessary and delegates the actual feature extraction to
 * the protected methods.
 */
void elapse::BaseFeatureExtractor::onSample(elapse::SamplePtr sample)
{
    if (windowStart == 0)
        return;
    Q_ASSERT(signalType != Signal::INVALID);

    if (sample->timestamp < windowStart)
        return;

    quint64 windowEnd = windowStart + windowLength * 1e6;
    quint64 nextWindowStart = windowStart + windowStep * 1e6;

    if (sample->timestamp >= windowEnd) {
        FeatureVector featureVector(signalType, windowStart);
        featureVector.features = features();
        emit newFeatures(featureVector);

        removeDataBefore(nextWindowStart);
        windowStart = nextWindowStart;
    }

    analyseSample(sample);
}

void elapse::BaseFeatureExtractor::reset()
{
    removeDataBefore(std::numeric_limits<quint64>::max());
}

/*!
 * \return the Signal::Type this FeatureExtractor works with, as defined
 * by the "SignalType" class info field.
 */
elapse::Signal::Type elapse::BaseFeatureExtractor::findSignalType() const
{
    const int index = metaObject()->indexOfClassInfo("SignalType");
    const char *info = metaObject()->classInfo(index).value();
    return Signal::fromString(info);
}
