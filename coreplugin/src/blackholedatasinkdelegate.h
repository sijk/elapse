#ifndef BLACKHOLEDATASINKDELEGATE_H
#define BLACKHOLEDATASINKDELEGATE_H

#include <elapse/elements/datasinkdelegate.h>


/*!
 * \brief The BlackHoleDataSinkDelegate class funnels data into the ether.
 * \ingroup core-plugin
 */

class BlackHoleDataSinkDelegate : public elapse::DataSinkDelegate
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BlackHoleDataSinkDelegate(QObject *parent = nullptr);

    bool start();
    void stop();
    bool needsNewSessionData();
    bool getSessionData();

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config);
    void saveData(elapse::Signal::Type signalType, QByteArray data);
    void saveSample(elapse::Signal::Type signalType, elapse::SamplePtr sample);
    void saveFeatureVector(elapse::FeatureVector featureVector);
    void saveCognitiveState(elapse::CognitiveState state);
};

#endif // BLACKHOLEDATASINKDELEGATE_H
