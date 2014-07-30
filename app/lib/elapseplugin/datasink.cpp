#include <QxtLogger>
#include "elapse/elements/datasink.h"

using elapse::Signal;


/*!
 * Create a new DataSink as a child of the given \a parent.
 */
elapse::DataSink::DataSink(QObject *parent) :
    QObject(parent)
{
}

/*!
 * Start saving data.
 *
 * This first checks whether it needsNewCaptureInfo() and calls
 * getCaptureInfo() if necessary.
 *
 * \return whether any necessary capture info was successfully retrieved
 * and saving was successfully started.
 */
bool elapse::DataSink::start()
{
    if (!needsNewCaptureInfo() || getCaptureInfo())
        return startSaving();
    return false;
}

/*!
 * Stop saving data.
 */
void elapse::DataSink::stop()
{
    stopSaving();
}

/*!
 * Called when the elapse::DataSource emits EEG \a data. Calls saveData().
 */
void elapse::DataSink::onEegData(QByteArray data)
{
    saveData(Signal::EEG, data);
}

/*!
 * Called when the elapse::DataSource emits video \a data. Calls saveData().
 */
void elapse::DataSink::onVideoData(QByteArray data)
{
    saveData(Signal::VIDEO, data);
}

/*!
 * Called when the elapse::DataSource emits IMU \a data. Calls saveData().
 */
void elapse::DataSink::onImuData(QByteArray data)
{
    saveData(Signal::IMU, data);
}

/*!
 * Called when a elapse::SampleDecoder emits an EEG \a sample. Calls
 * saveSample().
 */
void elapse::DataSink::onEegSample(elapse::SamplePtr sample)
{
    saveSample(Signal::EEG, sample);
}

/*!
 * Called when a elapse::SampleDecoder emits a video \a sample. Calls
 * saveSample().
 */
void elapse::DataSink::onVideoSample(elapse::SamplePtr sample)
{
    saveSample(Signal::VIDEO, sample);
}

/*!
 * Called when a elapse::SampleDecoder emits an IMU \a sample. Calls
 * saveSample().
 */
void elapse::DataSink::onImuSample(elapse::SamplePtr sample)
{
    saveSample(Signal::IMU, sample);
}

/*!
 * Called when a elapse::FeatureExtractor emits a \a featureVector. Calls
 * saveFeatureVector().
 */
void elapse::DataSink::onFeatureVector(elapse::FeatureVector featureVector)
{
    saveFeatureVector(featureVector);
}

/*!
 * Called when the elapse::Classifier emits a new cognitive \a state. Calls
 * saveCognitiveState().
 */
void elapse::DataSink::onCognitiveState(elapse::CognitiveState state)
{
    saveCognitiveState(state);
}

void elapse::DataSink::saveData(Signal::Type signalType, QByteArray data)
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

void elapse::DataSink::saveSample(Signal::Type signalType, elapse::SamplePtr sample)
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

void elapse::DataSink::saveFeatureVector(elapse::FeatureVector featureVector)
{
    Q_UNUSED(featureVector);

    static bool called = false;
    if (!called) {
        called = true;
        qxtLog->debug(metaObject()->className(),
                      "doesn't support saving feature vectors.");
    }
}

void elapse::DataSink::saveCognitiveState(elapse::CognitiveState state)
{
    Q_UNUSED(state);

    static bool called = false;
    if (!called) {
        called = true;
        qxtLog->debug(metaObject()->className(),
                      "doesn't support saving cognitive state.");
    }
}

