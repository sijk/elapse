#ifndef DUMMYVIDEOFEATUREEXTRACTOR_H
#define DUMMYVIDEOFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include "util/timestampedvalues.h"


/*!
 * \brief The DummyVideoFeatureExtractor class is a placeholder
 * FeatureExtractor for VideoSample%s.
 *
 * It outputs a two-element FeatureVector containing:
 *   -# the mean pixel intensity of all of the frames in the window,
 *   -# the variance of the mean pixel intensity of each frame in the window.
 *
 * \ingroup core-plugin
 */

class DummyVideoFeatureExtractor : public elapse::BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")

public:
    Q_INVOKABLE explicit DummyVideoFeatureExtractor(QObject *parent = nullptr);

    void setStartTime(quint64 timestamp);

protected:
    void analyseSample(elapse::SamplePtr sample);
    QVector<double> features();
    void removeDataBefore(quint64 time);

private:
    TimestampedValues<double> means;
};

#endif // DUMMYVIDEOFEATUREEXTRACTOR_H
