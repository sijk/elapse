#include "dummyeegfeatureextractor.h"

DummyEegFeatureExtractor::DummyEegFeatureExtractor(QObject *parent) :
    BaseFeatureExtractor(parent)
{
}

void DummyEegFeatureExtractor::analyseSample(elapse::SamplePtr sample)
{
    sampleFlags[sample->timestamp] = 1;
}

std::vector<double> DummyEegFeatureExtractor::features()
{
    return { double(sampleFlags.size()) };
}

void DummyEegFeatureExtractor::removeDataBefore(elapse::TimeStamp time)
{
    sampleFlags.removeValuesBefore(time);
}
