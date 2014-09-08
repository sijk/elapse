#include <QDataStream>
#include <elapse/datatypes.h>
#include "imudecoder.h"

namespace elapse { namespace coreplugin {

using elapse::data::ImuSample;
using elapse::data::SamplePtr;

/*!
 * Create a new ImuDecoder.
 */
ImuDecoder::ImuDecoder()
{
}

/*!
 * Decode the given \a data and emit elapse::ImuSample%s.
 */
void ImuDecoder::onData(QByteArray data)
{
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_4_6);

    auto sample = ImuSample::create();
    qint32 ax, ay, az;
    qint32 gx, gy, gz;

    stream >> sample->timestamp
           >> ax >> ay >> az
           >> gx >> gy >> gz;

    // TODO: scale by current full-scale range
    sample->acc = QVector3D(ax, ay, az);
    sample->gyr = QVector3D(gx, gy, gz);

    emit newSample(sample);
}

}} // namespace elapse::coreplugin
