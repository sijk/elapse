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

    bool startSaving();
    void stopSaving();
    bool needsNewCaptureInfo();
    bool getCaptureInfo();

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config);
    void saveData(data::Signal::Type signalType, QByteArray data);
    void saveSample(data::Signal::Type signalType, data::SamplePtr sample);
    void saveFeatureVector(data::FeatureVector featureVector);
    void saveCognitiveState(data::CognitiveState state);
};

}} // namespace elapse::coreplugin

#endif // BLACKHOLEDATASINK_H
