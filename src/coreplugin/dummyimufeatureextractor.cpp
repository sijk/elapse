#include "sampletypes.h"
#include "dummyimufeatureextractor.h"

DummyImuFeatureExtractor::DummyImuFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyImuFeatureExtractor::onSample(const Sample &sample)
{
    Q_UNUSED(sample)
}
