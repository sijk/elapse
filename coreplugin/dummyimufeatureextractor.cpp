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

void DummyImuFeatureExtractor::analyseSample(data::SamplePtr sample)
{
    if (headWidget)
        updateHeadWidget(*ImuSample::staticCastFrom(sample));

    sampleFlags[sample->timestamp] = 1;
}

std::vector<double> DummyImuFeatureExtractor::features()
{
    return { double(sampleFlags.size()) };
}

void DummyImuFeatureExtractor::removeDataBefore(time::Point time)
{
    sampleFlags.removeValuesBefore(time);
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
