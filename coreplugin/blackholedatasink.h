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

#ifndef BLACKHOLEDATASINK_H
#define BLACKHOLEDATASINK_H

#include <elapse/elements/datasink.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The BlackHoleDataSink class funnels data into the ether.
 * \ingroup core-plugin
 */

class BlackHoleDataSink : public elements::DataSink
{
    Q_OBJECT
public:
    Q_INVOKABLE BlackHoleDataSink();

    bool startSaving() override;
    void stopSaving() override;
    bool needsNewCaptureInfo() override;
    bool getCaptureInfo() override;

    void saveDeviceConfig(const QMap<QString, QVariantMap> &config) override;
    void saveData(data::Signal::Type signalType, QByteArray data) override;
    void saveSample(data::Signal::Type signalType, data::SamplePtr sample) override;
    void saveFeatureVector(data::FeatureVector::const_ptr featureVector) override;
    void saveCognitiveState(data::CognitiveState::const_ptr state) override;
};

}} // namespace elapse::coreplugin

#endif // BLACKHOLEDATASINK_H
