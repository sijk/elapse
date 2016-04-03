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
void BlackHoleDataSink::saveFeatureVector(FeatureVector::const_ptr featureVector)
{
    Q_UNUSED(featureVector)
}

/*!
 * Do nothing.
 */
void BlackHoleDataSink::saveCognitiveState(CognitiveState::const_ptr state)
{
    Q_UNUSED(state)
}

}} // namespace elapse::coreplugin
