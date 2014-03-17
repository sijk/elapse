#include <QDataStream>
#include <elapse/sampletypes.h>
#include "headwidget.h"
#include "imudecoder.h"

using elapse::ImuSample;
using elapse::SamplePtr;


/*!
 * Create a new ImuDecoder as a child of the given \a parent.
 */
ImuDecoder::ImuDecoder(QObject *parent) :
    SampleDecoder(parent),
    headWidget(nullptr)
{
}

/*!
 * \return a 3D head model widget whose orientation matches that
 * measured by the IMU.
 */
QWidget *ImuDecoder::getWidget()
{
    if (!headWidget)
        headWidget = new HeadWidget;
    return headWidget;
}

/*!
 * Decode the given \a data and emit ImuSample%s.
 */
void ImuDecoder::onData(QByteArray data)
{
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_4_6);

    auto sample = new ImuSample;
    qint32 ax, ay, az;
    qint32 gx, gy, gz;

    stream >> sample->timestamp
           >> ax >> ay >> az
           >> gx >> gy >> gz;

    // TODO: scale by current full-scale range
    sample->acc = QVector3D(ax, ay, az);
    sample->gyr = QVector3D(gx, gy, gz);

    if (headWidget)
        updateHeadWidget(sample);

    emit newSample(SamplePtr(sample));
}

/*!
 * Update the orientation of the head widget with the given \a sample.
 */
void ImuDecoder::updateHeadWidget(const ImuSample *sample)
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
