#ifndef DUMMYIMUFEATUREEXTRACTOR_H
#define DUMMYIMUFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"


/*!
 * \brief The DummyImuFeatureExtractor class is a black hole for ImuSample%s.
 *
 * \ingroup core-plugin
 */

class DummyImuFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "IMU")

public:
    Q_INVOKABLE explicit DummyImuFeatureExtractor(QObject *parent = nullptr);

    void setStartTime(quint64 timestamp);
    void setWindowLength(uint ms);
    void setWindowStep(uint ms);

public slots:
    void onSample(SamplePtr sample);
};

#endif // DUMMYIMUFEATUREEXTRACTOR_H
