#include "sampletypes.h"
#include "dummyimufeatureextractor.h"

DummyImuFeatureExtractor::DummyImuFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyImuFeatureExtractor::onSample(SamplePtr sample)
{
    Q_UNUSED(sample)
}
