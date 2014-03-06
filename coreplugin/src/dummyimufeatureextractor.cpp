#include "dummyimufeatureextractor.h"

DummyImuFeatureExtractor::DummyImuFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyImuFeatureExtractor::setStartTime(quint64 timestamp)
{
    Q_UNUSED(timestamp)
}

void DummyImuFeatureExtractor::setWindowLength(uint ms)
{
    Q_UNUSED(ms)
}

void DummyImuFeatureExtractor::setWindowStep(uint ms)
{
    Q_UNUSED(ms)
}

void DummyImuFeatureExtractor::onSample(SamplePtr sample)
{
    Q_UNUSED(sample)
}
