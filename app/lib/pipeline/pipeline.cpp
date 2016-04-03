/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#include <QVariant>
#include <QxtLogger>
#include "elapse/timestamps.h"
#include "pipeline.h"

namespace elapse { namespace client {

using namespace elapse::time::literals;
using elapse::data::Signal;

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
    qRegisterMetaType<elapse::data::SamplePtr>("elapse::data::SamplePtr");
}

/*!
 * \return the Pipeline's elements::ElementSet.
 */
const elements::ElementSet *Pipeline::elements() const
{
    return _elements.get();
}

/*!
 * Set the window length of all of the FeatureExtractor%s in \a ms.
 */
void Pipeline::setWindowLength(uint ms)
{
    for (auto featureExtractor : _elements->featureExtractors())
        featureExtractor->setWindowLength(ms);
}

/*!
 * Set the window step of all of the FeatureExtractor%s in \a ms.
 */
void Pipeline::setWindowStep(uint ms)
{
    for (auto featureExtractor : _elements->featureExtractors())
        featureExtractor->setWindowStep(ms);
}

/*!
 * Provide a new set of elements to the Pipeline.
 *
 * This method also sets up the connections between the elements and propagates
 * signals from elements to the Pipeline.
 *
 * elements::ElementSet lifetimes are handled automatically, so if you call
 * setElements() when the Pipeline already has an elements::ElementSet the
 * old set will be released (and destroyed if nothing else holds a reference
 * to it) and replaced by the new set.
 */
void Pipeline::setElements(elements::ElementSetPtr newElements)
{
    _elements = newElements;

    // Connect elements
    connect(_elements->dataSource(), SIGNAL(eegReady(QByteArray)),
            _elements->sampleDecoder(Signal::EEG), SLOT(onData(QByteArray)));
    connect(_elements->dataSource(), SIGNAL(videoReady(QByteArray)),
            _elements->sampleDecoder(Signal::VIDEO), SLOT(onData(QByteArray)));
    connect(_elements->dataSource(), SIGNAL(imuReady(QByteArray)),
            _elements->sampleDecoder(Signal::IMU), SLOT(onData(QByteArray)));

    connect(_elements->sampleDecoder(Signal::EEG), SIGNAL(newSample(elapse::data::SamplePtr)),
            _elements->featureExtractor(Signal::EEG), SLOT(onSample(elapse::data::SamplePtr)));
    connect(_elements->sampleDecoder(Signal::VIDEO), SIGNAL(newSample(elapse::data::SamplePtr)),
            _elements->featureExtractor(Signal::VIDEO), SLOT(onSample(elapse::data::SamplePtr)));
    connect(_elements->sampleDecoder(Signal::IMU), SIGNAL(newSample(elapse::data::SamplePtr)),
            _elements->featureExtractor(Signal::IMU), SLOT(onSample(elapse::data::SamplePtr)));

    connect(_elements->featureExtractor(Signal::EEG), SIGNAL(newFeatures(elapse::data::FeatureVector::const_ptr)),
            _elements->classifier(), SLOT(onFeatures(elapse::data::FeatureVector::const_ptr)));
    connect(_elements->featureExtractor(Signal::VIDEO), SIGNAL(newFeatures(elapse::data::FeatureVector::const_ptr)),
            _elements->classifier(), SLOT(onFeatures(elapse::data::FeatureVector::const_ptr)));
    connect(_elements->featureExtractor(Signal::IMU), SIGNAL(newFeatures(elapse::data::FeatureVector::const_ptr)),
            _elements->classifier(), SLOT(onFeatures(elapse::data::FeatureVector::const_ptr)));

    connect(_elements->classifier(), SIGNAL(newState(elapse::data::CognitiveState::const_ptr)),
            _elements->action(), SLOT(onState(elapse::data::CognitiveState::const_ptr)));

    // Propagate signals from elements
    connect(_elements->dataSource(), SIGNAL(started()), SIGNAL(started()));
    connect(_elements->dataSource(), SIGNAL(finished()), SIGNAL(error()));
    connect(_elements->dataSource(), SIGNAL(error(QString)), SIGNAL(error(QString)));
    for (auto decoder : _elements->sampleDecoders())
        connect(decoder, SIGNAL(error(QString)), SIGNAL(error(QString)));

    // Connect DataSink
    connect(_elements->dataSource(), SIGNAL(eegReady(QByteArray)),
            _elements->dataSink(), SLOT(onEegData(QByteArray)));
    connect(_elements->dataSource(), SIGNAL(videoReady(QByteArray)),
            _elements->dataSink(), SLOT(onVideoData(QByteArray)));
    connect(_elements->dataSource(), SIGNAL(imuReady(QByteArray)),
            _elements->dataSink(), SLOT(onImuData(QByteArray)));
    connect(_elements->sampleDecoder(Signal::EEG), SIGNAL(newSample(elapse::data::SamplePtr)),
            _elements->dataSink(), SLOT(onEegSample(elapse::data::SamplePtr)));
    connect(_elements->sampleDecoder(Signal::VIDEO), SIGNAL(newSample(elapse::data::SamplePtr)),
            _elements->dataSink(), SLOT(onVideoSample(elapse::data::SamplePtr)));
    connect(_elements->sampleDecoder(Signal::IMU), SIGNAL(newSample(elapse::data::SamplePtr)),
            _elements->dataSink(), SLOT(onImuSample(elapse::data::SamplePtr)));
    connect(_elements->featureExtractor(Signal::EEG), SIGNAL(newFeatures(elapse::data::FeatureVector::const_ptr)),
            _elements->dataSink(), SLOT(onFeatureVector(elapse::data::FeatureVector::const_ptr)));
    connect(_elements->featureExtractor(Signal::VIDEO), SIGNAL(newFeatures(elapse::data::FeatureVector::const_ptr)),
            _elements->dataSink(), SLOT(onFeatureVector(elapse::data::FeatureVector::const_ptr)));
    connect(_elements->featureExtractor(Signal::IMU), SIGNAL(newFeatures(elapse::data::FeatureVector::const_ptr)),
            _elements->dataSink(), SLOT(onFeatureVector(elapse::data::FeatureVector::const_ptr)));
    connect(_elements->classifier(), SIGNAL(newState(elapse::data::CognitiveState::const_ptr)),
            _elements->dataSink(), SLOT(onCognitiveState(elapse::data::CognitiveState::const_ptr)));

    // Watch for first sample to set start time
    connect(_elements->sampleDecoder(Signal::EEG), SIGNAL(newSample(elapse::data::SamplePtr)),
            SLOT(setStartTime(elapse::data::SamplePtr)));
    connect(_elements->sampleDecoder(Signal::VIDEO), SIGNAL(newSample(elapse::data::SamplePtr)),
            SLOT(setStartTime(elapse::data::SamplePtr)));
    connect(_elements->sampleDecoder(Signal::IMU), SIGNAL(newSample(elapse::data::SamplePtr)),
            SLOT(setStartTime(elapse::data::SamplePtr)));
}

/*!
 * Configure the elements::SampleDecoder%s  and elements::FeatureExtractor%s
 * to match the hardware \a config and also pass it to
 * elements::DataSink::saveDeviceConfig().
 */
void Pipeline::setDeviceConfig(QMap<QString, QVariantMap> config)
{
    for (auto sampleDecoder : _elements->sampleDecoders())
        sampleDecoder->configure(config);

    for (auto featureExtractor : _elements->featureExtractors())
        featureExtractor->configure(config);

    _elements->dataSink()->saveDeviceConfig(config);
}

/*!
 * Start the pipeline.
 */
void Pipeline::start()
{
    Q_ASSERT(_elements);

    startTimeIsSet = false;

    qxtLog->info("Starting pipeline");
    if (!_elements->dataSink()->start()) {
        emit error();
        return;
    }
    for (auto decoder : _elements->sampleDecoders())
        decoder->start();
    _elements->classifier()->reset();
    _elements->dataSource()->start();
}

/*!
 * Stop the pipeline.
 */
void Pipeline::stop()
{
    if (!_elements)
        return;

    qxtLog->info("Stopping pipeline");
    _elements->dataSource()->stop();
    for (auto decoder : _elements->sampleDecoders())
        decoder->stop();
    _elements->dataSink()->stop();
    emit stopped();
}

/*!
 * Called whenever a \a sample is decoded. For the first sample, it sets the
 * start timestamp for the FeatureExtractor%s to one second later to give all
 * of the sensors time to start up. For subsequent samples it does nothing.
 */
void Pipeline::setStartTime(data::SamplePtr sample)
{
    // Access to startTimeIsSet doesn't need special synchronisation
    // as long as this slot is connected with Qt::AutoConnection so that
    // it's called from the main thread (same thread as start()).
    if (startTimeIsSet)
        return;

    time::Point startTime = sample->timestamp + 1_s;

    qxtLog->debug("Setting start time to", time::format(startTime));
    for (auto featureExtractor : _elements->featureExtractors())
        featureExtractor->setStartTime(startTime);

    startTimeIsSet = true;
}

/*!
 * \fn Pipeline::started()
 * Emitted when the elements::DataSource has started receiving data from
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

}} // namespace elapse::client
