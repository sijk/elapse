#ifndef BLACKHOLEDATASINK_H
#define BLACKHOLEDATASINK_H

#include <elapse/elements/datasink.h>


/*!
 * \brief The BlackHoleDataSink class funnels data into the ether.
 * \ingroup core-plugin
 */

class BlackHoleDataSink : public elapse::DataSink
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BlackHoleDataSink(QObject *parent = nullptr);

    bool startSaving();
    void stopSaving();
    bool needsNewCaptureInfo();
    bool getCaptureInfo();

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config);
    void saveData(elapse::Signal::Type signalType, QByteArray data);
    void saveSample(elapse::Signal::Type signalType, elapse::SamplePtr sample);
    void saveFeatureVector(elapse::FeatureVector featureVector);
    void saveCognitiveState(elapse::CognitiveState state);
};

#endif // BLACKHOLEDATASINK_H
