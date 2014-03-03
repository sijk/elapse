#include "sampletypes.h"
#include "dummyeegfeatureextractor.h"

DummyEegFeatureExtractor::DummyEegFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyEegFeatureExtractor::onSample(SamplePtr sample)
{
    Q_UNUSED(sample)
}
