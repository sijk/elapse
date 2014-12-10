#ifndef BLACKHOLEDATASINK_H
#define BLACKHOLEDATASINK_H

#include <elapse/elements/datasink.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The BlackHoleDataSink class funnels data into the ether.
 * \ingroup core-plugin
 */

class BlackHoleDataSink : public elements::DataSink
{
    Q_OBJECT
public:
    Q_INVOKABLE BlackHoleDataSink();

    bool startSaving() override;
    void stopSaving() override;
    bool needsNewCaptureInfo() override;
    bool getCaptureInfo() override;

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config) override;
    void saveData(data::Signal::Type signalType, QByteArray data) override;
    void saveSample(data::Signal::Type signalType, data::SamplePtr sample) override;
    void saveFeatureVector(data::FeatureVector::const_ptr featureVector) override;
    void saveCognitiveState(data::CognitiveState::const_ptr state) override;
};

}} // namespace elapse::coreplugin

#endif // BLACKHOLEDATASINK_H
