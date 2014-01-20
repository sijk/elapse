#include <QDataStream>
#include "sampletypes.h"
#include "imudecoder.h"

ImuDecoder::ImuDecoder(QObject *parent) :
    SampleDecoder(parent)
{
}

/*!
 * Decode the given \a data and emit \ref ImuSample "ImuSamples".
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

    emit newSample(SamplePtr(sample));
}
