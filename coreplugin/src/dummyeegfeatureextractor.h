#ifndef DUMMYEEGFEATUREEXTRACTOR_H
#define DUMMYEEGFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"


/*!
 * \brief The DummyEegFeatureExtractor class is a black hole for EegSample%s.
 *
 * \ingroup core-plugin
 */

class DummyEegFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "EEG")

public:
    Q_INVOKABLE explicit DummyEegFeatureExtractor(QObject *parent = nullptr);

    void setStartTime(quint64 timestamp);
    void setWindowLength(uint ms);
    void setWindowStep(uint ms);

public slots:
    void onSample(SamplePtr sample);
};

#endif // DUMMYEEGFEATUREEXTRACTOR_H
