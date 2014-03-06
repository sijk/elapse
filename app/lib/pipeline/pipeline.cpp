#include <QVariant>
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
    qRegisterMetaType<SamplePtr>("SamplePtr");
}

/*!
 * \return the Pipeline's ElementSet.
 */
ElementSetPtr Pipeline::elements() const
{
    return _elements;
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
            _elements->sampleDecoders[SampleType::EEG], SLOT(onData(QByteArray)));
    connect(_elements->dataSource, SIGNAL(videoReady(QByteArray)),
            _elements->sampleDecoders[SampleType::VIDEO], SLOT(onData(QByteArray)));
    connect(_elements->dataSource, SIGNAL(imuReady(QByteArray)),
            _elements->sampleDecoders[SampleType::IMU], SLOT(onData(QByteArray)));

    connect(_elements->sampleDecoders[SampleType::EEG], SIGNAL(newSample(SamplePtr)),
            _elements->featureExtractors[SampleType::EEG], SLOT(onSample(SamplePtr)));
    connect(_elements->sampleDecoders[SampleType::VIDEO], SIGNAL(newSample(SamplePtr)),
            _elements->featureExtractors[SampleType::VIDEO], SLOT(onSample(SamplePtr)));
    connect(_elements->sampleDecoders[SampleType::IMU], SIGNAL(newSample(SamplePtr)),
            _elements->featureExtractors[SampleType::IMU], SLOT(onSample(SamplePtr)));

    // Propagate signals from elements
    connect(_elements->dataSource, SIGNAL(started()), SIGNAL(started()));
    connect(_elements->dataSource, SIGNAL(error(QString)), SIGNAL(error(QString)));
}

/*!
 * Start the pipeline.
 */
void Pipeline::start()
{
    if (!_elements) {
        emit error("The pipeline is not configured.");
        return;
    }

    _elements->dataSource->start();
}

/*!
 * Stop the pipeline.
 */
void Pipeline::stop()
{
    if (!_elements)
        return;

    _elements->dataSource->stop();
    emit stopped();
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
