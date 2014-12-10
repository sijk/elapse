#include <QDataStream>
#include <elapse/datatypes.h>
#include "imudecoder.h"

namespace elapse { namespace coreplugin {

/*!
 * Create a new ImuDecoder.
 */
ImuDecoder::ImuDecoder()
{
}

/*!
 * Decode the given \a data and emit data::ImuSample%s.
 */
void ImuDecoder::onData(QByteArray data)
{
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_4_6);

    auto sample = data::ImuSample::create();
    qint32 ax, ay, az;
    qint32 gx, gy, gz;

    stream >> sample->timestamp
           >> ax >> ay >> az
           >> gx >> gy >> gz;

    sample->acc = QVector3D(ax, ay, az);
    sample->gyr = QVector3D(gx, gy, gz);

    emit newSample(sample);
}

}} // namespace elapse::coreplugin
