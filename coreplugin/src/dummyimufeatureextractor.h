#ifndef DUMMYIMUFEATUREEXTRACTOR_H
#define DUMMYIMUFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"
#include "util/timestampedvalues.h"


/*!
 * \brief The DummyImuFeatureExtractor class is a black hole for ImuSample%s.
 *
 * \ingroup core-plugin
 */

class DummyImuFeatureExtractor : public BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "IMU")

public:
    Q_INVOKABLE explicit DummyImuFeatureExtractor(QObject *parent = nullptr);

protected:
    void analyseSample(SamplePtr sample);
    QVector<double> features();
    void removeDataBefore(quint64 time);

private:
    TimestampedValues<int> sampleFlags;
};

#endif // DUMMYIMUFEATUREEXTRACTOR_H
