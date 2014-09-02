#ifndef FEATUREXTRACTOR_P_H
#define FEATUREXTRACTOR_P_H

#include "elapse/elements/featurextractor.h"

namespace elapse {

class BaseFeatureExtractorPrivate
{
public:
    BaseFeatureExtractorPrivate();

    time::Point windowStart;
    uint windowLength;
    uint windowStep;
    Signal::Type signalType;

    static Signal::Type findSignalType(BaseFeatureExtractor *q);
    static BaseFeatureExtractorPrivate *expose(BaseFeatureExtractor *q);
};

} // namespace elapse

#endif // FEATUREXTRACTOR_P_H
