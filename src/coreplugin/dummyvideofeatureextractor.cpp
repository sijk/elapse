#include "sampletypes.h"
#include "dummyvideofeatureextractor.h"

DummyVideoFeatureExtractor::DummyVideoFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyVideoFeatureExtractor::onSample(SamplePtr sample)
{
    Q_UNUSED(sample)
}
