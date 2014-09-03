#include "headwidget.h"
#include "dummyimufeatureextractor.h"

namespace elapse { namespace coreplugin {

using namespace elapse;
using namespace elapse::data;


DummyImuFeatureExtractor::DummyImuFeatureExtractor() :
    headWidget(nullptr)
{
}

/*!
 * \return a 3D head model widget whose orientation matches that
 * measured by the IMU.
 */
QWidget *DummyImuFeatureExtractor::getWidget()
{
    if (!headWidget)
        headWidget = new HeadWidget;
    return headWidget;
}

void DummyImuFeatureExtractor::analyseSample(SamplePtr sample)
{
    if (headWidget)
        updateHeadWidget(ImuSample::staticCastFrom(sample).get());

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
void DummyImuFeatureExtractor::updateHeadWidget(const ImuSample *sample)
{
    // Calculate the direction of the acceleration vector.
    // By assuming this is purely due to gravity, we get an approximation
    // of the head orientation (though with no information about z rotation).
    float ax = sample->acc.x();
    float ay = sample->acc.y();
    float az = sample->acc.z();
    double theta = atan2(ax, az);
    double phi = atan2(ay, sqrt(ax*ax + az*az));

    headWidget->setXRotation(-theta);
    headWidget->setZRotation(phi);
}

}} // namespace elapse::coreplugin
