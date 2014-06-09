#ifndef DUMMYIMUFEATUREEXTRACTOR_H
#define DUMMYIMUFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include <elapse/displayable.h>

class HeadWidget;


/*!
 * \brief The DummyImuFeatureExtractor class is a black hole for ImuSample%s.
 *
 * It exposes a 3D head model widget which displays the measured orientation.
 *
 * \ingroup core-plugin
 */

class DummyImuFeatureExtractor : public elapse::BaseFeatureExtractor,
                                 public elapse::Displayable
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "IMU")

public:
    Q_INVOKABLE explicit DummyImuFeatureExtractor(QObject *parent = nullptr);

    QWidget *getWidget();

private:
    void analyseSample(elapse::SamplePtr sample);
    std::vector<double> features();
    void removeDataBefore(elapse::TimeStamp time);

    void updateHeadWidget(const elapse::ImuSample *sample);

    HeadWidget *headWidget;
    elapse::time::Series<int> sampleFlags;
};

#endif // DUMMYIMUFEATUREEXTRACTOR_H
