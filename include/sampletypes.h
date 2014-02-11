#ifndef SAMPLETYPES_H
#define SAMPLETYPES_H

#include <QtGlobal>
#include <QVector>
#include <QByteArray>
#include <QSharedPointer>


enum SampleType
{
    EEG, VIDEO, IMU,
    N_SAMPLE_TYPES
};


struct Sample
{
    virtual ~Sample() {}

    quint64 timestamp;
};


typedef QSharedPointer<const Sample> SamplePtr;


struct EegSample : Sample
{
    quint32 seqnum;
    quint16 leadOff;
    QVector<double> values;
};


struct VideoSample : Sample
{
    int w, h;
    QByteArray data;
};


struct ImuSample : Sample
{
};


#endif // SAMPLETYPES_H
