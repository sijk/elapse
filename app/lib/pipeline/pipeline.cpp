#include <QVariant>
#include <QxtLogger>
#include "elapse/timestamps.h"
#include "pipeline.h"

using namespace elapse::time::literals;

/*!
 * \page pipeline-arch Signal Pipeline Structure
 *
 * @startuml{pipeline-arch-class.png}
 *
 * hide class circle
 * hide class attributes
 * skinparam packageBorderColor white
 * skinparam shadowing false
 *
 * class dataSource {
 *      eegReady()
 *      videoReady()
 *      imuReady()
 * }
 * package {
 *      class "sampleDecoders[EEG]" {
 *          onData()
 *          newSample()
 *      }
 *      class "sampleDecoders[VIDEO]" {
 *          onData()
 *          newSample()
 *      }
 *      class "sampleDecoders[IMU]" {
 *          onData()
 *          newSample()
 *      }
 * }
 * package {
 *      class "featureExtractors[EEG]" {
 *          onSample()
 *          newFeatures()
 *      }
 *      class "featureExtractors[VIDEO]" {
 *          onSample()
 *          newFeatures()
 *      }
 *      class "featureExtractors[IMU]" {
 *          onSample()
 *          newFeatures()
 *      }
 * }
 * class classifier {
 *      onFeatures()
 *      newState()
 * }
 * class outputAction {
 *      onState()
 * }
 *
 * dataSource -> "sampleDecoders[EEG]" : QByteArray
 * dataSource -> "sampleDecoders[VIDEO]" : QByteArray
 * dataSource -> "sampleDecoders[IMU]" : QByteArray
 * "sampleDecoders[EEG]" -> "featureExtractors[EEG]" : EegSample
 * "sampleDecoders[VIDEO]" -> "featureExtractors[VIDEO]" : VideoSample
 * "sampleDecoders[IMU]" -> "featureExtractors[IMU]" : ImuSample
 * "featureExtractors[EEG]" -> classifier : FeatureVector
 * "featureExtractors[VIDEO]" -> classifier : FeatureVector
 * "featureExtractors[IMU]" -> classifier : FeatureVector
 * classifier --> outputAction : CognitiveState
 *
 * @enduml
 */

/*!
 * Construct a new Pipeline as a child of the given \a parent.
 */
Pipeline::Pipeline(QObject *parent) :
    QObject(parent),
    _elements(nullptr)
{
    qRegisterMetaType<elapse::SamplePtr>("elapse::SamplePtr");
}

/*!
 * \return the Pipeline's ElementSet.
 */
ElementSetPtr Pipeline::elements() const
{
    return _elements;
}

/*!
 * Set the window length of all of the FeatureExtractor%s in \a ms.
 */
void Pipeline::setWindowLength(uint ms)
{
    foreach(auto &featureExtractor, _elements->featureExtractors)
        featureExtractor->setWindowLength(ms);
}

/*!
 * Set the window step of all of the FeatureExtractor%s in \a ms.
 */
void Pipeline::setWindowStep(uint ms)
{
    foreach(auto &featureExtractor, _elements->featureExtractors)
        featureExtractor->setWindowStep(ms);
}

/*!
 * Provide a new set of elements to the Pipeline.
 *
 * This method also sets up the connections between the elements and propagates
 * signals from elements to the Pipeline.
 *
 * ElementSet lifetimes are handled automatically, so if you call setElements()
 * when the Pipeline already has an ElementSet the old set will be released
 * (and destroyed if nothing else holds a reference to it) and replaced by the
 * new set.
 */
void Pipeline::setElements(ElementSetPtr newElements)
{
    _elements = newElements;

    // Connect elements
    connect(_elements->dataSource.data(), SIGNAL(eegReady(QByteArray)),
            _elements->sampleDecoders[Signal::EEG].data(), SLOT(onData(QByteArray)));
    connect(_elements->dataSource.data(), SIGNAL(videoReady(QByteArray)),
            _elements->sampleDecoders[Signal::VIDEO].data(), SLOT(onData(QByteArray)));
    connect(_elements->dataSource.data(), SIGNAL(imuReady(QByteArray)),
            _elements->sampleDecoders[Signal::IMU].data(), SLOT(onData(QByteArray)));

    connect(_elements->sampleDecoders[Signal::EEG].data(), SIGNAL(newSample(elapse::SamplePtr)),
            _elements->featureExtractors[Signal::EEG].data(), SLOT(onSample(elapse::SamplePtr)));
    connect(_elements->sampleDecoders[Signal::VIDEO].data(), SIGNAL(newSample(elapse::SamplePtr)),
            _elements->featureExtractors[Signal::VIDEO].data(), SLOT(onSample(elapse::SamplePtr)));
    connect(_elements->sampleDecoders[Signal::IMU].data(), SIGNAL(newSample(elapse::SamplePtr)),
            _elements->featureExtractors[Signal::IMU].data(), SLOT(onSample(elapse::SamplePtr)));

    connect(_elements->featureExtractors[Signal::EEG].data(), SIGNAL(newFeatures(elapse::FeatureVector)),
            _elements->classifier.data(), SLOT(onFeatures(elapse::FeatureVector)));
    connect(_elements->featureExtractors[Signal::VIDEO].data(), SIGNAL(newFeatures(elapse::FeatureVector)),
            _elements->classifier.data(), SLOT(onFeatures(elapse::FeatureVector)));
    connect(_elements->featureExtractors[Signal::IMU].data(), SIGNAL(newFeatures(elapse::FeatureVector)),
            _elements->classifier.data(), SLOT(onFeatures(elapse::FeatureVector)));

    connect(_elements->classifier.data(), SIGNAL(newState(elapse::CognitiveState)),
            _elements->action.data(), SLOT(onState(elapse::CognitiveState)));

    // Propagate signals from elements
    connect(_elements->dataSource.data(), SIGNAL(started()), SIGNAL(started()));
    connect(_elements->dataSource.data(), SIGNAL(finished()), SIGNAL(error()));
    connect(_elements->dataSource.data(), SIGNAL(error(QString)), SIGNAL(error(QString)));
    foreach (auto &decoder, _elements->sampleDecoders)
        connect(decoder.data(), SIGNAL(error(QString)), SIGNAL(error(QString)));

    // Connect DataSink
    connect(_elements->dataSource.data(), SIGNAL(eegReady(QByteArray)),
            _elements->dataSink.data(), SLOT(onEegData(QByteArray)));
    connect(_elements->dataSource.data(), SIGNAL(videoReady(QByteArray)),
            _elements->dataSink.data(), SLOT(onVideoData(QByteArray)));
    connect(_elements->dataSource.data(), SIGNAL(imuReady(QByteArray)),
            _elements->dataSink.data(), SLOT(onImuData(QByteArray)));
    connect(_elements->sampleDecoders[Signal::EEG].data(), SIGNAL(newSample(elapse::SamplePtr)),
            _elements->dataSink.data(), SLOT(onEegSample(elapse::SamplePtr)));
    connect(_elements->sampleDecoders[Signal::VIDEO].data(), SIGNAL(newSample(elapse::SamplePtr)),
            _elements->dataSink.data(), SLOT(onVideoSample(elapse::SamplePtr)));
    connect(_elements->sampleDecoders[Signal::IMU].data(), SIGNAL(newSample(elapse::SamplePtr)),
            _elements->dataSink.data(), SLOT(onImuSample(elapse::SamplePtr)));
    connect(_elements->featureExtractors[Signal::EEG].data(), SIGNAL(newFeatures(elapse::FeatureVector)),
            _elements->dataSink.data(), SLOT(onFeatureVector(elapse::FeatureVector)));
    connect(_elements->featureExtractors[Signal::VIDEO].data(), SIGNAL(newFeatures(elapse::FeatureVector)),
            _elements->dataSink.data(), SLOT(onFeatureVector(elapse::FeatureVector)));
    connect(_elements->featureExtractors[Signal::IMU].data(), SIGNAL(newFeatures(elapse::FeatureVector)),
            _elements->dataSink.data(), SLOT(onFeatureVector(elapse::FeatureVector)));
    connect(_elements->classifier.data(), SIGNAL(newState(elapse::CognitiveState)),
            _elements->dataSink.data(), SLOT(onCognitiveState(elapse::CognitiveState)));

    // Watch for first sample to set start time
    connect(_elements->sampleDecoders[Signal::EEG].data(), SIGNAL(newSample(elapse::SamplePtr)),
            SLOT(setStartTime(elapse::SamplePtr)));
    connect(_elements->sampleDecoders[Signal::VIDEO].data(), SIGNAL(newSample(elapse::SamplePtr)),
            SLOT(setStartTime(elapse::SamplePtr)));
    connect(_elements->sampleDecoders[Signal::IMU].data(), SIGNAL(newSample(elapse::SamplePtr)),
            SLOT(setStartTime(elapse::SamplePtr)));
}

/*!
 * Start the pipeline.
 */
void Pipeline::start()
{
    Q_ASSERT(_elements);

    startTimeIsSet = false;

    qxtLog->info("Starting pipeline");
    if (!_elements->dataSink->start()) {
        emit error();
        return;
    }
    foreach (auto &decoder, _elements->sampleDecoders)
        decoder->start();
    _elements->classifier->reset();
    _elements->dataSource->start();
}

/*!
 * Stop the pipeline.
 */
void Pipeline::stop()
{
    if (!_elements)
        return;

    qxtLog->info("Stopping pipeline");
    _elements->dataSource->stop();
    foreach (auto &decoder, _elements->sampleDecoders)
        decoder->stop();
    _elements->dataSink->stop();
    emit stopped();
}

/*!
 * Called whenever a \a sample is decoded. For the first sample, it sets the
 * start timestamp for the FeatureExtractor%s to one second later to give all
 * of the sensors time to start up. For subsequent samples it does nothing.
 */
void Pipeline::setStartTime(elapse::SamplePtr sample)
{
    // Access to startTimeIsSet doesn't need special synchronisation
    // as long as this slot is connected with Qt::AutoConnection so that
    // it's called from the main thread (same thread as start()).
    if (startTimeIsSet)
        return;

    elapse::TimeStamp startTime = sample->timestamp + 1_s;

    qxtLog->debug("Setting start time to", elapse::time::format(startTime));
    foreach (auto &featureExtractor, _elements->featureExtractors)
        featureExtractor->setStartTime(startTime);

    startTimeIsSet = true;
}

/*!
 * \fn Pipeline::started()
 * Emitted when the elapse::DataSource has started receiving data from
 * the device.
 */

/*!
 * \fn Pipeline::stopped()
 * Emitted when data has stopped flowing through the pipeline for any reason.
 */

/*!
 * \fn Pipeline::error(QString msg)
 * Emitted when an error has occurred somewhere in the pipeline. The \a msg is
 * human readable, suitable for displaying in a dialog box or similar.
 */
