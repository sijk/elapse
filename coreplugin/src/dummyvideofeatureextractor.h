#ifndef DUMMYVIDEOFEATUREEXTRACTOR_H
#define DUMMYVIDEOFEATUREEXTRACTOR_H

#include "elements/featurextractor.h"


/*!
 * \brief The DummyVideoFeatureExtractor class is a black hole for
 * VideoSample%s.
 *
 * \ingroup core-plugin
 */

class DummyVideoFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SampleType", "VIDEO")

public:
    Q_INVOKABLE explicit DummyVideoFeatureExtractor(QObject *parent = nullptr);

    void setStartTime(quint64 timestamp);
    void setWindowLength(uint ms);
    void setWindowStep(uint ms);

public slots:
    void onSample(SamplePtr sample);
};

#endif // DUMMYVIDEOFEATUREEXTRACTOR_H
