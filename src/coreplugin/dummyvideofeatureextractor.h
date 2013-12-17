#ifndef DUMMYVIDEOFEATUREEXTRACTOR_H
#define DUMMYVIDEOFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"

class Sample;


/*!
 * \brief The DummyVideoFeatureExtractor class is a black hole for
 * \ref VideoSample "VideoSamples".
 *
 * \ingroup core-plugin
 */

class DummyVideoFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "VIDEO")

public:
    Q_INVOKABLE explicit DummyVideoFeatureExtractor(QObject *parent = nullptr);

public slots:
    void onSample(SamplePtr sample);
};

#endif // DUMMYVIDEOFEATUREEXTRACTOR_H
