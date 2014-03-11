#include "dummyeegfeatureextractor.h"

DummyEegFeatureExtractor::DummyEegFeatureExtractor(QObject *parent) :
    BaseFeatureExtractor(parent)
{
}

void DummyEegFeatureExtractor::analyseSample(SamplePtr sample)
{
    sampleFlags.insert(sample->timestamp, 1);
}

QVector<double> DummyEegFeatureExtractor::features()
{
    return QVector<double>() << sampleFlags.size();
}

void DummyEegFeatureExtractor::removeDataBefore(quint64 time)
{
    sampleFlags.removeValuesBefore(time);
}
