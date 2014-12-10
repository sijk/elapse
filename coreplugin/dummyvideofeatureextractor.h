#ifndef DUMMYVIDEOFEATUREEXTRACTOR_H
#define DUMMYVIDEOFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include <elapse/timestamps.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The DummyVideoFeatureExtractor class is a placeholder
 * elements::FeatureExtractor for data::VideoSample%s.
 *
 * It outputs a two-element data::FeatureVector containing:
 *   -# the mean pixel intensity of all of the frames in the window,
 *   -# the variance of the mean pixel intensity of each frame in the window.
 *
 * \ingroup core-plugin
 */

class DummyVideoFeatureExtractor : public elements::BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")

public:
    Q_INVOKABLE DummyVideoFeatureExtractor();

    void setStartTime(time::Point timestamp) override;

protected:
    void analyseSample(data::SamplePtr sample) override;
    std::vector<double> features() override;
    void removeDataBefore(time::Point time) override;

private:
    time::Series<double> means;
};

}} // namespace elapse::coreplugin

#endif // DUMMYVIDEOFEATUREEXTRACTOR_H
