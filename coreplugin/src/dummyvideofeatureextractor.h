#ifndef DUMMYVIDEOFEATUREEXTRACTOR_H
#define DUMMYVIDEOFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include <elapse/timestamps.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The DummyVideoFeatureExtractor class is a placeholder
 * FeatureExtractor for VideoSample%s.
 *
 * It outputs a two-element FeatureVector containing:
 *   -# the mean pixel intensity of all of the frames in the window,
 *   -# the variance of the mean pixel intensity of each frame in the window.
 *
 * \ingroup core-plugin
 */

class DummyVideoFeatureExtractor : public elapse::elements::BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")

public:
    Q_INVOKABLE DummyVideoFeatureExtractor();

    void setStartTime(elapse::time::Point timestamp);

protected:
    void analyseSample(elapse::data::SamplePtr sample);
    std::vector<double> features();
    void removeDataBefore(elapse::time::Point time);

private:
    elapse::time::Series<double> means;
};

}} // namespace elapse::coreplugin

#endif // DUMMYVIDEOFEATUREEXTRACTOR_H
