#include <algorithm>
#include <QxtLogger>
#include "dummyvideofeatureextractor.h"


template<class Container, class T = double>
T sum(const Container &c)
{
    return std::accumulate(c.cbegin(), c.cend(), T());
}


/*!
 * Create a DummyVideoFeatureExtractor.
 */
DummyVideoFeatureExtractor::DummyVideoFeatureExtractor()
{
}

void DummyVideoFeatureExtractor::setStartTime(elapse::time::Point timestamp)
{
    BaseFeatureExtractor::setStartTime(timestamp);
    means.clear();
}

/*!
 * Calculate the mean intensity of the pixels in the given \a sample.
 */
void DummyVideoFeatureExtractor::analyseSample(elapse::SamplePtr sample)
{
    auto frame = elapse::VideoSample::staticCastFrom(sample);
    double meanIntensity = sum(frame->data) / (frame->w * frame->h);
    means[frame->timestamp] = meanIntensity;
}

/*!
 * \return the feature vector for the current window. See the class overview
 * for details of the contents of the feature vector.
 */
std::vector<double> DummyVideoFeatureExtractor::features()
{
    auto meanVals = means.values();
    double meanIntensity = sum(meanVals) / meanVals.size();

    double sumSqDiff = std::accumulate(meanVals.cbegin(), meanVals.cend(), 0.0,
        [=](double acc, double x) {
            return acc + (meanIntensity - x) * (meanIntensity - x);
        });
    double meanSqDiff = sumSqDiff / meanVals.size();

    return { meanIntensity, meanSqDiff };
}

void DummyVideoFeatureExtractor::removeDataBefore(elapse::time::Point time)
{
    means.removeValuesBefore(time);
}
