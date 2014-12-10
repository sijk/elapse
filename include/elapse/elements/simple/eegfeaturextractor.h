#ifndef SIMPLE_EEGFEATUREXTRACTOR_H
#define SIMPLE_EEGFEATUREXTRACTOR_H

#include <Eigen/Core>
#include "elapse/elements/featurextractor.h"
#include "elapse/timestamps.h"

namespace elapse { namespace elements {

/*!
 * \brief The SimpleEegFeatureExtractor class is a convenient base class for
 * implementing EEG FeatureExtractor%s.
 *
 * The only method you need to implement is extractFeatures().
 *
 * \headerfile elapse/elements/simple/eegfeaturextractor.h
 */

class SimpleEegFeatureExtractor : public BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    void configure(QMap<QString, QVariantMap> config) override;

protected:
    void analyseSample(data::SamplePtr sample) final;
    std::vector<double> features() final;
    void removeDataBefore(time::Point time) final;

    /*!
     * Extract features from the given \a eeg matrix. Each column of the EEG
     * matrix corresponds to a channel of EEG. The number of rows should be
     * equal to the [window length](\ref FeatureExtractor::setWindowLength)
     * times the \a sampleRate, though it may be slightly less if any samples
     * were dropped. (If you need to detect dropped samples you'll need to
     * inherit from BaseFeatureExtractor instead of this class.)
     *
     * \return a std::vector of extracted features.
     */
    virtual std::vector<double> extractFeatures(const Eigen::MatrixXd &eeg,
                                                uint sampleRate) = 0;

private:
    uint sampFreq = 0;
    time::Series<data::EegSample::const_ptr> samples;
};

}} // namespace elapse::elements

#endif // SIMPLE_EEGFEATUREXTRACTOR_H
