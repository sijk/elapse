#ifndef DUMMYEEGFEATUREEXTRACTOR_H
#define DUMMYEEGFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"

class Sample;


/*!
 * \brief The DummyEegFeatureExtractor class is a black hole for
 * \ref EegSample "EegSamples".
 *
 * \ingroup core-plugin
 */

class DummyEegFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "EEG")

public:
    Q_INVOKABLE explicit DummyEegFeatureExtractor(QObject *parent = nullptr);

public slots:
    void onSample(SamplePtr sample);
};

#endif // DUMMYEEGFEATUREEXTRACTOR_H
