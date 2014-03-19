#ifndef DUMMYIMUFEATUREEXTRACTOR_H
#define DUMMYIMUFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include "util/timestampedvalues.h"


/*!
 * \brief The DummyImuFeatureExtractor class is a black hole for ImuSample%s.
 *
 * \ingroup core-plugin
 */

class DummyImuFeatureExtractor : public elapse::BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "IMU")

public:
    Q_INVOKABLE explicit DummyImuFeatureExtractor(QObject *parent = nullptr);

protected:
    void analyseSample(elapse::SamplePtr sample);
    QVector<double> features();
    void removeDataBefore(quint64 time);

private:
    TimestampedValues<int> sampleFlags;
};

#endif // DUMMYIMUFEATUREEXTRACTOR_H
