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

#ifndef DUMMYIMUFEATUREEXTRACTOR_H
#define DUMMYIMUFEATUREEXTRACTOR_H

#include <QPointer>
#include <array>
#include <elapse/elements/featurextractor.h>
#include <elapse/displayable.h>

namespace elapse {
namespace widgets { class HeadWidget; }
namespace coreplugin {


/*!
 * \brief The DummyImuFeatureExtractor class is a black hole for
 * data::ImuSample%s.
 *
 * It exposes a [3D head model widget](\ref widgets::HeadWidget)
 * which displays the measured orientation.
 *
 * \ingroup core-plugin
 */

class DummyImuFeatureExtractor : public elements::BaseFeatureExtractor,
                                 public elapse::Displayable
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "IMU")

public:
    Q_INVOKABLE DummyImuFeatureExtractor();

    QWidget *getWidget() override;

private:
    void analyseSample(data::SamplePtr sample) override;
    std::vector<double> features() override;
    void removeDataBefore(time::Point time) override;

    void updateHeadWidget(const data::ImuSample &sample);

    QPointer<widgets::HeadWidget> headWidget;
    time::Series<std::array<float, 6>> samples;
};

}} // namespace elapse::coreplugin

#endif // DUMMYIMUFEATUREEXTRACTOR_H
