#ifndef FEATUREXTRACTOR_P_H
#define FEATUREXTRACTOR_P_H

#include "elapse/elements/featurextractor.h"

namespace elapse { namespace elements {

class BaseFeatureExtractorPrivate
{
public:
    BaseFeatureExtractorPrivate();

    time::Point windowStart;
    uint windowLength;
    uint windowStep;
    data::Signal::Type signalType;

    static data::Signal::Type findSignalType(BaseFeatureExtractor *q);
    static BaseFeatureExtractorPrivate *expose(BaseFeatureExtractor *q);
};

}} // namespace elapse::elements

#endif // FEATUREXTRACTOR_P_H
