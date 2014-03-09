#include <algorithm>
#include <QxtLogger>
#include "dummyvideofeatureextractor.h"


template<class Container, class T = double>
T sum(const Container &c)
{
    return std::accumulate(c.constBegin(), c.constEnd(), T());
}


/*!
 * Create a DummyVideoFeatureExtractor as a child of the given \a parent.
 */
DummyVideoFeatureExtractor::DummyVideoFeatureExtractor(QObject *parent) :
    BaseFeatureExtractor(parent)
{
}

void DummyVideoFeatureExtractor::setStartTime(quint64 timestamp)
{
    BaseFeatureExtractor::setStartTime(timestamp);
    means.clear();
}

/*!
 * Calculate the mean intensity of the pixels in the given \a sample.
 */
void DummyVideoFeatureExtractor::analyseSample(SamplePtr sample)
{
    auto frame = sample.staticCast<const VideoSample>();
    double meanIntensity = sum(frame->data) / (frame->w * frame->h);
    means.insert(frame->timestamp, meanIntensity);
}

/*!
 * \return the feature vector for the current window. See the class overview
 * for details of the contents of the feature vector.
 */
FeatureVector DummyVideoFeatureExtractor::featureVector()
{
    double meanIntensity = sum(means) / means.size();

    double sumSqDiff = std::accumulate(means.cbegin(), means.cend(), 0.0,
        [=](double acc, double x) {
            return acc + (meanIntensity - x) * (meanIntensity - x);
        });
    double meanSqDiff = sumSqDiff / means.size();

    FeatureVector features;
    features << meanIntensity << meanSqDiff;
    return features;
}

void DummyVideoFeatureExtractor::removeDataBefore(quint64 time)
{
    means.removeValuesBefore(time);
}
