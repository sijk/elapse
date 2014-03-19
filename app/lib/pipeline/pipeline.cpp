#include <QVariant>
#include <QxtLogger>
#include "pipeline.h"

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
 *
 * dataSource -> "sampleDecoders[EEG]" : QByteArray
 * dataSource -> "sampleDecoders[VIDEO]" : QByteArray
 * dataSource -> "sampleDecoders[IMU]" : QByteArray
 * "sampleDecoders[EEG]" -> "featureExtractors[EEG]" : EegSample
 * "sampleDecoders[VIDEO]" -> "featureExtractors[VIDEO]" : VideoSample
 * "sampleDecoders[IMU]" -> "featureExtractors[IMU]" : ImuSample
 * "featureExtractors[EEG]" -> classifier : EegFeatures
 * "featureExtractors[VIDEO]" -> classifier : VideoFeatures
 * "featureExtractors[IMU]" -> classifier : ImuFeatures
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
    qRegisterMetaType<elapse::SamplePtr>("SamplePtr");
}

/*!
 * \return the Pipeline's ElementSet.
 */
ElementSetPtr Pipeline::elements() const
{
    return _elements;
}

/*!
 * Set the window length of all of the FeatutreExtractor%s in \a ms.
 */
void Pipeline::setWindowLength(uint ms)
{
    foreach(auto featureExtractor, _elements->featureExtractors)
        featureExtractor->setWindowLength(ms);
}

/*!
 * Set the window step of all of the FeatutreExtractor%s in \a ms.
 */
void Pipeline::setWindowStep(uint ms)
{
    foreach(auto featureExtractor, _elements->featureExtractors)
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
    connect(_elements->dataSource, SIGNAL(eegReady(QByteArray)),
            _elements->sampleDecoders[Signal::EEG], SLOT(onData(QByteArray)));
    connect(_elements->dataSource, SIGNAL(videoReady(QByteArray)),
            _elements->sampleDecoders[Signal::VIDEO], SLOT(onData(QByteArray)));
    connect(_elements->dataSource, SIGNAL(imuReady(QByteArray)),
            _elements->sampleDecoders[Signal::IMU], SLOT(onData(QByteArray)));

    connect(_elements->sampleDecoders[Signal::EEG], SIGNAL(newSample(SamplePtr)),
            _elements->featureExtractors[Signal::EEG], SLOT(onSample(SamplePtr)));
    connect(_elements->sampleDecoders[Signal::VIDEO], SIGNAL(newSample(SamplePtr)),
            _elements->featureExtractors[Signal::VIDEO], SLOT(onSample(SamplePtr)));
    connect(_elements->sampleDecoders[Signal::IMU], SIGNAL(newSample(SamplePtr)),
            _elements->featureExtractors[Signal::IMU], SLOT(onSample(SamplePtr)));

    connect(_elements->featureExtractors[Signal::EEG], SIGNAL(newFeatures(FeatureVector)),
            _elements->classifier, SLOT(onFeatures(FeatureVector)));
    connect(_elements->featureExtractors[Signal::VIDEO], SIGNAL(newFeatures(FeatureVector)),
            _elements->classifier, SLOT(onFeatures(FeatureVector)));
    connect(_elements->featureExtractors[Signal::IMU], SIGNAL(newFeatures(FeatureVector)),
            _elements->classifier, SLOT(onFeatures(FeatureVector)));

    // Propagate signals from elements
    connect(_elements->dataSource, SIGNAL(started()), SIGNAL(started()));
    connect(_elements->dataSource, SIGNAL(error(QString)), SIGNAL(error(QString)));
}

/*!
 * Start the pipeline.
 */
void Pipeline::start()
{
    Q_ASSERT(_elements);

    connect(_elements->sampleDecoders[Signal::EEG],
            SIGNAL(newSample(SamplePtr)), SLOT(setStartTime(SamplePtr)));

    qxtLog->info("Starting pipeline");
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
    emit stopped();

    disconnect(_elements->sampleDecoders[Signal::EEG],
               SIGNAL(newSample(SamplePtr)), this, 0);
}

/*!
 * Called when the first \a sample is decoded. Sets the start timestamp for
 * the FeatureExtractor%s to one second after that to give all of the sensors
 * time to start up.
 */
void Pipeline::setStartTime(elapse::SamplePtr sample)
{
    quint64 startTime = sample->timestamp + 1e9;

    qxtLog->debug("Setting start time to", startTime / 1e9);
    foreach (auto featureExtractor, _elements->featureExtractors)
        featureExtractor->setStartTime(startTime);

    disconnect(_elements->sampleDecoders[Signal::EEG],
               SIGNAL(newSample(SamplePtr)), this, 0);
}

/*!
 * \fn Pipeline::started()
 * Emitted when the DataSource has started receiving data from the device.
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
