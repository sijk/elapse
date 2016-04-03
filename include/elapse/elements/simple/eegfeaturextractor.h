/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

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
