#include <algorithm>
#include <QxtLogger>
#include "dummyvideofeatureextractor.h"

using elapse::VideoSample;
using elapse::SamplePtr;


template<class Container, class T = double>
T sum(const Container &c)
{
    return std::accumulate(c.cbegin(), c.cend(), T());
}


/*!
 * Create a DummyVideoFeatureExtractor as a child of the given \a parent.
 */
DummyVideoFeatureExtractor::DummyVideoFeatureExtractor(QObject *parent) :
    BaseFeatureExtractor(parent)
{
}

void DummyVideoFeatureExtractor::setStartTime(elapse::TimeStamp timestamp)
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
    means[frame->timestamp] = meanIntensity;
}

/*!
 * \return the feature vector for the current window. See the class overview
 * for details of the contents of the feature vector.
 */
QVector<double> DummyVideoFeatureExtractor::features()
{
    auto meanVals = means.values();
    double meanIntensity = sum(meanVals) / meanVals.size();

    double sumSqDiff = std::accumulate(meanVals.cbegin(), meanVals.cend(), 0.0,
        [=](double acc, double x) {
            return acc + (meanIntensity - x) * (meanIntensity - x);
        });
    double meanSqDiff = sumSqDiff / meanVals.size();

    QVector<double> features;
    features << meanIntensity << meanSqDiff;
    return features;
}

void DummyVideoFeatureExtractor::removeDataBefore(elapse::TimeStamp time)
{
    means.removeValuesBefore(time);
}
