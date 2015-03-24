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
