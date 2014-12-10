#ifndef DUMMYEEGFEATUREEXTRACTOR_H
#define DUMMYEEGFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include <elapse/timestamps.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The DummyEegFeatureExtractor class is a black hole for
 * data::EegSample%s.
 *
 * \ingroup core-plugin
 */

class DummyEegFeatureExtractor : public elements::BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE DummyEegFeatureExtractor();

protected:
    void analyseSample(data::SamplePtr sample) override;
    std::vector<double> features() override;
    void removeDataBefore(time::Point time) override;

private:
    time::Series<int> sampleFlags;
};

}} // namespace elapse::coreplugin

#endif // DUMMYEEGFEATUREEXTRACTOR_H
