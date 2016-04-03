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
void DataSink::onFeatureVector(FeatureVector::const_ptr featureVector)
{
    saveFeatureVector(featureVector);
}

/*!
 * Called when the Classifier emits a new cognitive \a state. Calls
 * saveCognitiveState().
 */
void DataSink::onCognitiveState(CognitiveState::const_ptr state)
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

void DataSink::saveFeatureVector(FeatureVector::const_ptr featureVector)
{
    Q_UNUSED(featureVector);

    static bool called = false;
    if (!called) {
        called = true;
        qxtLog->debug(metaObject()->className(),
                      "doesn't support saving feature vectors.");
    }
}

void DataSink::saveCognitiveState(CognitiveState::const_ptr state)
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
