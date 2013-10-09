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


#endif // SAMPLETYPES_H
