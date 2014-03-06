#include "dummyeegfeatureextractor.h"

DummyEegFeatureExtractor::DummyEegFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyEegFeatureExtractor::setStartTime(quint64 timestamp)
{
    Q_UNUSED(timestamp)
}

void DummyEegFeatureExtractor::setWindowLength(uint ms)
{
    Q_UNUSED(ms)
}

void DummyEegFeatureExtractor::setWindowStep(uint ms)
{
    Q_UNUSED(ms)
}

void DummyEegFeatureExtractor::onSample(SamplePtr sample)
{
    Q_UNUSED(sample)
}
