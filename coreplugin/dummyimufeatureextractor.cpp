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

#include "headwidget.h"
#include "dummyimufeatureextractor.h"

namespace elapse { namespace coreplugin {

using elapse::data::ImuSample;


DummyImuFeatureExtractor::DummyImuFeatureExtractor() :
    headWidget(nullptr)
{
}

/*!
 * \return a widgets::HeadWidget whose orientation matches that
 * measured by the IMU.
 */
QWidget *DummyImuFeatureExtractor::getWidget()
{
    if (!headWidget)
        headWidget = new widgets::HeadWidget;
    return headWidget;
}

/*!
 * Update the head widget and save the IMU readings for later.
 */
void DummyImuFeatureExtractor::analyseSample(data::SamplePtr sample)
{
    const auto &imu = *ImuSample::staticCastFrom(sample);

    if (headWidget)
        updateHeadWidget(imu);

    samples.emplace(imu.timestamp, std::array<float,6>{
        imu.acc.x(), imu.acc.y(), imu.acc.z(),
        imu.gyr.x(), imu.gyr.y(), imu.gyr.z(),
    });
}

/*!
 * \return the mean of each axis of the IMU samples in the current window.
 */
std::vector<double> DummyImuFeatureExtractor::features()
{
    if (samples.empty())
        return {};

    std::vector<double> feat;
    feat.reserve(6);

    for (int i = 0; i < 6; i++) {
        double sum = 0;
        for (auto &s : samples)
            sum += s.second[i];
        feat.emplace_back(sum / samples.size());
    }

    return feat;
}

void DummyImuFeatureExtractor::removeDataBefore(time::Point time)
{
    samples.removeValuesBefore(time);
}

/*!
 * Update the orientation of the head widget with the given \a sample.
 */
void DummyImuFeatureExtractor::updateHeadWidget(const data::ImuSample &sample)
{
    // Calculate the direction of the acceleration vector.
    // By assuming this is purely due to gravity, we get an approximation
    // of the head orientation (though with no information about z rotation).
    float ax = sample.acc.x();
    float ay = sample.acc.y();
    float az = sample.acc.z();
    double xrot = atan2(ay, az);
    double yrot = atan2(ax, sqrt(ay*ay + az*az));

    headWidget->setXRotation(xrot);
    headWidget->setYRotation(yrot);
}

}} // namespace elapse::coreplugin
