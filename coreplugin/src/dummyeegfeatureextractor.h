#ifndef DUMMYEEGFEATUREEXTRACTOR_H
#define DUMMYEEGFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"
#include "util/timestampedvalues.h"


/*!
 * \brief The DummyEegFeatureExtractor class is a black hole for EegSample%s.
 *
 * \ingroup core-plugin
 */

class DummyEegFeatureExtractor : public BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE explicit DummyEegFeatureExtractor(QObject *parent = nullptr);

protected:
    void analyseSample(SamplePtr sample);
    QVector<double> features();
    void removeDataBefore(quint64 time);

private:
    TimestampedValues<int> sampleFlags;
};

#endif // DUMMYEEGFEATUREEXTRACTOR_H
