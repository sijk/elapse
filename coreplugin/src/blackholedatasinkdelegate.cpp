#include <QMessageBox>
#include <QApplication>
#include "blackholedatasinkdelegate.h"


/*!
 * Create a new BlackHoleDataSinkDelegate as a child of the given \a parent.
 */
BlackHoleDataSinkDelegate::BlackHoleDataSinkDelegate(QObject *parent) :
    DataSinkDelegate(parent)
{
}

/*!
 * Do nothing.
 */
bool BlackHoleDataSinkDelegate::start()
{
    return true;
}

/*!
 * Do nothing.
 */
void BlackHoleDataSinkDelegate::stop()
{
}

/*!
 * No capture info is needed since all data is discarded.
 */
bool BlackHoleDataSinkDelegate::needsNewCaptureInfo()
{
    return false;
}

/*!
 * Show a message box explaining that no capture info is necessary.
 */
bool BlackHoleDataSinkDelegate::getCaptureInfo()
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
void BlackHoleDataSinkDelegate::saveDeviceConfig(const QMap<QString, QVariantMap> &config)
{
    Q_UNUSED(config)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSinkDelegate::saveData(elapse::Signal::Type signalType,
                                         QByteArray data)
{
    Q_UNUSED(signalType)
    Q_UNUSED(data)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSinkDelegate::saveSample(elapse::Signal::Type signalType,
                                           elapse::SamplePtr sample)
{
    Q_UNUSED(signalType)
    Q_UNUSED(sample)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSinkDelegate::saveFeatureVector(elapse::FeatureVector featureVector)
{
    Q_UNUSED(featureVector)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSinkDelegate::saveCognitiveState(elapse::CognitiveState state)
{
    Q_UNUSED(state)
}

