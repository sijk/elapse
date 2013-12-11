#ifndef SAMPLETYPES_H
#define SAMPLETYPES_H

#include <QtGlobal>
#include <QVector>


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


struct EegSample : Sample
{
    quint32 seqnum;
    quint8 loff_stat_p;
    quint8 loff_stat_n;
    quint8 gpio;
    QVector<double> values;
};


struct VideoSample : Sample
{
};


struct ImuSample : Sample
{
};


#endif // SAMPLETYPES_H
