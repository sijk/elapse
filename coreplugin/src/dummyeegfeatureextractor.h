#ifndef DUMMYEEGFEATUREEXTRACTOR_H
#define DUMMYEEGFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include <elapse/timestamps.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The DummyEegFeatureExtractor class is a black hole for EegSample%s.
 *
 * \ingroup core-plugin
 */

class DummyEegFeatureExtractor : public elapse::elements::BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE DummyEegFeatureExtractor();

protected:
    void analyseSample(elapse::data::SamplePtr sample);
    std::vector<double> features();
    void removeDataBefore(elapse::time::Point time);

private:
    elapse::time::Series<int> sampleFlags;
};

}} // namespace elapse::coreplugin

#endif // DUMMYEEGFEATUREEXTRACTOR_H
