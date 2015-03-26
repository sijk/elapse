#ifndef DUMMYIMUFEATUREEXTRACTOR_H
#define DUMMYIMUFEATUREEXTRACTOR_H

#include <QPointer>
#include <array>
#include <elapse/elements/featurextractor.h>
#include <elapse/displayable.h>

namespace elapse {
namespace widgets { class HeadWidget; }
namespace coreplugin {


/*!
 * \brief The DummyImuFeatureExtractor class is a black hole for
 * data::ImuSample%s.
 *
 * It exposes a [3D head model widget](\ref widgets::HeadWidget)
 * which displays the measured orientation.
 *
 * \ingroup core-plugin
 */

class DummyImuFeatureExtractor : public elements::BaseFeatureExtractor,
                                 public elapse::Displayable
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "IMU")

public:
    Q_INVOKABLE DummyImuFeatureExtractor();

    QWidget *getWidget() override;

private:
    void analyseSample(data::SamplePtr sample) override;
    std::vector<double> features() override;
    void removeDataBefore(time::Point time) override;

    void updateHeadWidget(const data::ImuSample &sample);

    QPointer<widgets::HeadWidget> headWidget;
    time::Series<std::array<float, 6>> samples;
};

}} // namespace elapse::coreplugin

#endif // DUMMYIMUFEATUREEXTRACTOR_H
