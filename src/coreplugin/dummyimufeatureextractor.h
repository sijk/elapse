#ifndef DUMMYIMUFEATUREEXTRACTOR_H
#define DUMMYIMUFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"

class Sample;


/*!
 * \brief The DummyImuFeatureExtractor class is a black hole for
 * \ref ImuSample "ImuSamples".
 *
 * \ingroup core-plugin
 */

class DummyImuFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "IMU")

public:
    Q_INVOKABLE explicit DummyImuFeatureExtractor(QObject *parent = nullptr);

public slots:
    void onSample(const Sample &sample);
};

#endif // DUMMYIMUFEATUREEXTRACTOR_H
