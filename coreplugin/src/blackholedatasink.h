#ifndef BLACKHOLEDATASINK_H
#define BLACKHOLEDATASINK_H

#include <elapse/elements/datasink.h>


/*!
 * \brief The BlackHoleDataSink class funnels data into the ether.
 * \ingroup core-plugin
 */

class BlackHoleDataSink : public elapse::elements::DataSink
{
    Q_OBJECT
public:
    Q_INVOKABLE BlackHoleDataSink();

    bool startSaving();
    void stopSaving();
    bool needsNewCaptureInfo();
    bool getCaptureInfo();

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config);
    void saveData(elapse::data::Signal::Type signalType, QByteArray data);
    void saveSample(elapse::data::Signal::Type signalType, elapse::data::SamplePtr sample);
    void saveFeatureVector(elapse::data::FeatureVector featureVector);
    void saveCognitiveState(elapse::data::CognitiveState state);
};

#endif // BLACKHOLEDATASINK_H
