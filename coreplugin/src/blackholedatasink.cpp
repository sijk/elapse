#include <QMessageBox>
#include <QApplication>
#include "blackholedatasink.h"


/*!
 * Create a new BlackHoleDataSink as a child of the given \a parent.
 */
BlackHoleDataSink::BlackHoleDataSink(QObject *parent) :
    DataSink(parent)
{
}

/*!
 * Do nothing.
 */
bool BlackHoleDataSink::startSaving()
{
    return true;
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::stopSaving()
{
}

/*!
 * No capture info is needed since all data is discarded.
 */
bool BlackHoleDataSink::needsNewCaptureInfo()
{
    return false;
}

/*!
 * Show a message box explaining that no capture info is necessary.
 */
bool BlackHoleDataSink::getCaptureInfo()
{
    QMessageBox::information(qApp->activeWindow(), "Black hole",
                             "The black hole data sink doesn't need any\n"
                             "capture info — all data is discarded.",
                             QMessageBox::Ok);
    return true;
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveDeviceConfig(const QMap<QString, QVariantMap> &config)
{
    Q_UNUSED(config)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveData(elapse::Signal::Type signalType,
                                         QByteArray data)
{
    Q_UNUSED(signalType)
    Q_UNUSED(data)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveSample(elapse::Signal::Type signalType,
                                           elapse::SamplePtr sample)
{
    Q_UNUSED(signalType)
    Q_UNUSED(sample)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveFeatureVector(elapse::FeatureVector featureVector)
{
    Q_UNUSED(featureVector)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveCognitiveState(elapse::CognitiveState state)
{
    Q_UNUSED(state)
}

