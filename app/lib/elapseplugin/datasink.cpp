#include <QxtLogger>
#include "elapse/elements/datasink.h"

using namespace elapse::data;

namespace elapse { namespace elements {

/*!
 * Start saving data.
 *
 * This first checks whether it needsNewCaptureInfo() and calls
 * getCaptureInfo() if necessary.
 *
 * \return whether any necessary capture info was successfully retrieved
 * and saving was successfully started.
 */
bool DataSink::start()
{
    if (!needsNewCaptureInfo() || getCaptureInfo())
        return startSaving();
    return false;
}

/*!
 * Stop saving data.
 */
void DataSink::stop()
{
    stopSaving();
}

/*!
 * Called when the DataSource emits EEG \a data. Calls saveData().
 */
void DataSink::onEegData(QByteArray data)
{
    saveData(Signal::EEG, data);
}

/*!
 * Called when the DataSource emits video \a data. Calls saveData().
 */
void DataSink::onVideoData(QByteArray data)
{
    saveData(Signal::VIDEO, data);
}

/*!
 * Called when the DataSource emits IMU \a data. Calls saveData().
 */
void DataSink::onImuData(QByteArray data)
{
    saveData(Signal::IMU, data);
}

/*!
 * Called when a SampleDecoder emits an EEG \a sample. Calls
 * saveSample().
 */
void DataSink::onEegSample(SamplePtr sample)
{
    saveSample(Signal::EEG, sample);
}

/*!
 * Called when a SampleDecoder emits a video \a sample. Calls
 * saveSample().
 */
void DataSink::onVideoSample(SamplePtr sample)
{
    saveSample(Signal::VIDEO, sample);
}

/*!
 * Called when a SampleDecoder emits an IMU \a sample. Calls
 * saveSample().
 */
void DataSink::onImuSample(SamplePtr sample)
{
    saveSample(Signal::IMU, sample);
}

/*!
 * Called when a FeatureExtractor emits a \a featureVector. Calls
 * saveFeatureVector().
 */
void DataSink::onFeatureVector(FeatureVector featureVector)
{
    saveFeatureVector(featureVector);
}

/*!
 * Called when the Classifier emits a new cognitive \a state. Calls
 * saveCognitiveState().
 */
void DataSink::onCognitiveState(CognitiveState state)
{
    saveCognitiveState(state);
}

void DataSink::saveData(Signal::Type signalType, QByteArray data)
{
    Q_UNUSED(signalType);
    Q_UNUSED(data);

    static bool called = false;
    if (!called) {
        called = true;
        qxtLog->debug(metaObject()->className(),
                      "doesn't support saving raw data.");
    }
}

void DataSink::saveSample(Signal::Type signalType, SamplePtr sample)
{
    Q_UNUSED(signalType);
    Q_UNUSED(sample);

    static bool called = false;
    if (!called) {
        called = true;
        qxtLog->debug(metaObject()->className(),
                      "doesn't support saving samples.");
    }
}

void DataSink::saveFeatureVector(FeatureVector featureVector)
{
    Q_UNUSED(featureVector);

    static bool called = false;
    if (!called) {
        called = true;
        qxtLog->debug(metaObject()->className(),
                      "doesn't support saving feature vectors.");
    }
}

void DataSink::saveCognitiveState(CognitiveState state)
{
    Q_UNUSED(state);

    static bool called = false;
    if (!called) {
        called = true;
        qxtLog->debug(metaObject()->className(),
                      "doesn't support saving cognitive state.");
    }
}

}} // namespace elapse::elements
