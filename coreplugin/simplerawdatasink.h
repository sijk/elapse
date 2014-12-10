#ifndef SIMPLERAWDATASINK_H
#define SIMPLERAWDATASINK_H

#include <QDir>
#include <QFile>
#include <QTime>
#include <elapse/elements/datasink.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The SimpleRawDataSink class dumps raw data to disk using a
 * QDataStream.
 *
 * The only capture info required for this sink is the directory into
 * which the data files will be saved.
 *
 * Note that this class only supports saving raw data — not data::Sample%s or
 * data::FeatureVector%s or data::CognitiveState. The saved data can be loaded
 * again by a SimpleRawDataSource.
 *
 * \ingroup core-plugin
 */

class SimpleRawDataSink : public elements::DataSink
{
    Q_OBJECT
public:
    Q_INVOKABLE SimpleRawDataSink();

    bool startSaving();
    void stopSaving();
    bool needsNewCaptureInfo();
    bool getCaptureInfo();

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config);
    void saveData(data::Signal::Type signalType, QByteArray data);

protected:
    virtual QString getDirectory() const;

private:
    QDir dataDir;
    QFile file;
    QDataStream stream;
    QTime time;
};

}} // namespace elapse::coreplugin

#endif // SIMPLERAWDATASINK_H
