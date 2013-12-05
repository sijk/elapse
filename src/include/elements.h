#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "sampletypes.h"
#include "elements/datasource.h"
#include "elements/decoder.h"
class FeatureExtractor;
class Classifier;

struct ElementSet
{
    DataSource *dataSource;
    SampleDecoder *sampleDecoders[N_SAMPLE_TYPES];
    FeatureExtractor *featureExtractors[N_SAMPLE_TYPES];
    Classifier *classifier;
};

#endif // ELEMENTS_H