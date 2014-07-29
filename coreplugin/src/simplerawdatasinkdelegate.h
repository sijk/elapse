#ifndef SIMPLERAWDATASINKDELEGATE_H
#define SIMPLERAWDATASINKDELEGATE_H

#include <QDir>
#include <QFile>
#include <QTime>
#include <elapse/elements/datasinkdelegate.h>


/*!
 * \brief The SimpleRawDataSinkDelegate class dumps raw data to disk using a
 * QDataStream.
 *
 * The only capture info required for this delegate is the directory into
 * which the data files will be saved.
 *
 * Note that this class only supports saving raw data — not Sample%s or
 * FeatureVector%s or CognitiveState. The saved data can be loaded again by a
 * SimpleRawDataSource.
 *
 * \ingroup core-plugin
 */

class SimpleRawDataSinkDelegate : public elapse::DataSinkDelegate
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SimpleRawDataSinkDelegate(QObject *parent = nullptr);

    bool start();
    void stop();
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

#endif // SIMPLERAWDATASINKDELEGATE_H
