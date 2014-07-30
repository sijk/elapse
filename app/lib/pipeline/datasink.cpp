#include "elapse/elements/datasinkdelegate.h"
#include "datasink.h"

using elapse::Signal;


/*!
 * Create a new DataSink as a child of the given \a parent.
 */
DataSink::DataSink(QObject *parent) :
    QObject(parent)
{
}

/*!
 * Set the \a delegate for storing data to disk.
 */
void DataSink::setDelegate(elapse::DataSinkDelegate *delegate)
{
    this->delegate = delegate;
}

/*!
 * Store the device \a config to be saved once the delegate start()%s.
 */
void DataSink::saveDeviceConfig(const QMap<QString, QVariantMap> &config)
{
    Q_ASSERT(delegate);
    delegate->saveDeviceConfig(config);
}

/*!
 * Start saving data.
 *
 * This first checks whether the elapse::DataSinkDelegate::needsNewCaptureInfo()
 * and calls elapse::DataSinkDelegate::getCaptureInfo() if necessary.
 *
 * If the delegate was started succssfully, the device configuration is passed
 * to the delegate to be saved. This means that setDeviceConfig() must be
 * called before start().
 *
 * \return whether the delegate was able to retrieve any necessary capture info
 * and start successfully.
 */
bool DataSink::start()
{
    Q_ASSERT(delegate);

    if (!delegate->needsNewCaptureInfo() || delegate->getCaptureInfo())
        return delegate->start();

    return false;
}

/*!
 * Stop saving data.
 */
void DataSink::stop()
{
    Q_ASSERT(delegate);
    delegate->stop();
}

/*!
 * Called when the elapse::DataSource emits EEG \a data. Calls
 * elapse::DataSinkDelegate::saveData().
 */
void DataSink::onEegData(QByteArray data)
{
    Q_ASSERT(delegate);
    delegate->saveData(Signal::EEG, data);
}

/*!
 * Called when the elapse::DataSource emits video \a data. Calls
 * elapse::DataSinkDelegate::saveData().
 */
void DataSink::onVideoData(QByteArray data)
{
    Q_ASSERT(delegate);
    delegate->saveData(Signal::VIDEO, data);
}

/*!
 * Called when the elapse::DataSource emits IMU \a data. Calls
 * elapse::DataSinkDelegate::saveData().
 */
void DataSink::onImuData(QByteArray data)
{
    Q_ASSERT(delegate);
    delegate->saveData(Signal::IMU, data);
}

/*!
 * Called when a elapse::SampleDecoder emits an EEG \a sample. Calls
 * elapse::DataSinkDelegate::saveSample().
 */
void DataSink::onEegSample(elapse::SamplePtr sample)
{
    Q_ASSERT(delegate);
    delegate->saveSample(Signal::EEG, sample);
}

/*!
 * Called when a elapse::SampleDecoder emits a video \a sample. Calls
 * elapse::DataSinkDelegate::saveSample().
 */
void DataSink::onVideoSample(elapse::SamplePtr sample)
{
    Q_ASSERT(delegate);
    delegate->saveSample(Signal::VIDEO, sample);
}

/*!
 * Called when a elapse::SampleDecoder emits an IMU \a sample. Calls
 * elapse::DataSinkDelegate::saveSample().
 */
void DataSink::onImuSample(elapse::SamplePtr sample)
{
    Q_ASSERT(delegate);
    delegate->saveSample(Signal::IMU, sample);
}

/*!
 * Called when a elapse::FeatureExtractor emits a \a featureVector. Calls
 * elapse::DataSinkDelegate::saveFeatureVector().
 */
void DataSink::onFeatureVector(elapse::FeatureVector featureVector)
{
    Q_ASSERT(delegate);
    delegate->saveFeatureVector(featureVector);
}

/*!
 * Called when the elapse::Classifier emits a new cognitive \a state. Calls
 * elapse::DataSinkDelegate::saveCognitiveState().
 */
void DataSink::onCognitiveState(elapse::CognitiveState state)
{
    Q_ASSERT(delegate);
    delegate->saveCognitiveState(state);
}

