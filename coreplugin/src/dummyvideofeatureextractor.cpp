#include "dummyvideofeatureextractor.h"

DummyVideoFeatureExtractor::DummyVideoFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyVideoFeatureExtractor::setStartTime(quint64 timestamp)
{
    Q_UNUSED(timestamp)
}

void DummyVideoFeatureExtractor::setWindowLength(uint ms)
{
    Q_UNUSED(ms)
}

void DummyVideoFeatureExtractor::setWindowStep(uint ms)
{
    Q_UNUSED(ms)
}

void DummyVideoFeatureExtractor::onSample(SamplePtr sample)
{
    Q_UNUSED(sample)
}
