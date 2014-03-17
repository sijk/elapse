#include "dummyimufeatureextractor.h"

DummyImuFeatureExtractor::DummyImuFeatureExtractor(QObject *parent) :
    BaseFeatureExtractor(parent)
{
}

void DummyImuFeatureExtractor::analyseSample(elapse::SamplePtr sample)
{
    sampleFlags.insert(sample->timestamp, 1);
}

QVector<double> DummyImuFeatureExtractor::features()
{
    return QVector<double>() << sampleFlags.size();
}

void DummyImuFeatureExtractor::removeDataBefore(quint64 time)
{
    sampleFlags.removeValuesBefore(time);
}
