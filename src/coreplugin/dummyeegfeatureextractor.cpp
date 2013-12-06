#include "sampletypes.h"
#include "dummyeegfeatureextractor.h"

DummyEegFeatureExtractor::DummyEegFeatureExtractor(QObject *parent) :
    FeatureExtractor(parent)
{
}

void DummyEegFeatureExtractor::onSample(const Sample &sample)
{
    Q_UNUSED(sample)
}
