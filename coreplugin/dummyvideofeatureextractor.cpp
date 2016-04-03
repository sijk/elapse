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

#include <algorithm>
#include <QxtLogger>
#include "dummyvideofeatureextractor.h"


template<class Container, class T = double>
T sum(const Container &c)
{
    return std::accumulate(c.cbegin(), c.cend(), T());
}


namespace elapse { namespace coreplugin {

using elapse::data::VideoSample;

/*!
 * Create a DummyVideoFeatureExtractor.
 */
DummyVideoFeatureExtractor::DummyVideoFeatureExtractor()
{
}

void DummyVideoFeatureExtractor::setStartTime(time::Point timestamp)
{
    BaseFeatureExtractor::setStartTime(timestamp);
    means.clear();
}

/*!
 * Calculate the mean intensity of the pixels in the given \a sample.
 */
void DummyVideoFeatureExtractor::analyseSample(data::SamplePtr sample)
{
    auto frame = VideoSample::staticCastFrom(sample);
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

void DummyVideoFeatureExtractor::removeDataBefore(time::Point time)
{
    means.removeValuesBefore(time);
}

}} // namespace elapse::coreplugin
