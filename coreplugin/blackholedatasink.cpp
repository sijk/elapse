#include <QMessageBox>
#include <QApplication>
#include "blackholedatasink.h"

namespace elapse { namespace coreplugin {

using namespace elapse::data;


/*!
 * Create a new BlackHoleDataSink.
 */
BlackHoleDataSink::BlackHoleDataSink()
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
void BlackHoleDataSink::saveData(Signal::Type signalType, QByteArray data)
{
    Q_UNUSED(signalType)
    Q_UNUSED(data)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveSample(Signal::Type signalType, SamplePtr sample)
{
    Q_UNUSED(signalType)
    Q_UNUSED(sample)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveFeatureVector(FeatureVector featureVector)
{
    Q_UNUSED(featureVector)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveCognitiveState(CognitiveState state)
{
    Q_UNUSED(state)
}

}} // namespace elapse::coreplugin
