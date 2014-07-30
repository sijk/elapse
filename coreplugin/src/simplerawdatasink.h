#ifndef SIMPLERAWDATASINK_H
#define SIMPLERAWDATASINK_H

#include <QDir>
#include <QFile>
#include <QTime>
#include <elapse/elements/datasink.h>


/*!
 * \brief The SimpleRawDataSink class dumps raw data to disk using a
 * QDataStream.
 *
 * The only capture info required for this sink is the directory into
 * which the data files will be saved.
 *
 * Note that this class only supports saving raw data — not Sample%s or
 * FeatureVector%s or CognitiveState. The saved data can be loaded again by a
 * SimpleRawDataSource.
 *
 * \ingroup core-plugin
 */

class SimpleRawDataSink : public elapse::DataSink
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SimpleRawDataSink(QObject *parent = nullptr);

    bool startSaving();
    void stopSaving();
    bool needsNewCaptureInfo();
    bool getCaptureInfo();

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config);
    void saveData(elapse::Signal::Type signalType, QByteArray data);

protected:
    virtual QString getDirectory() const;

private:
    QDir dataDir;
    QFile file;
    QDataStream stream;
    QTime time;
};

#endif // SIMPLERAWDATASINK_H
