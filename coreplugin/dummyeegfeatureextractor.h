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

#ifndef DUMMYEEGFEATUREEXTRACTOR_H
#define DUMMYEEGFEATUREEXTRACTOR_H

#include <elapse/elements/featurextractor.h>
#include <elapse/timestamps.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The DummyEegFeatureExtractor class is a black hole for
 * data::EegSample%s.
 *
 * \ingroup core-plugin
 */

class DummyEegFeatureExtractor : public elements::BaseFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE DummyEegFeatureExtractor();

protected:
    void analyseSample(data::SamplePtr sample) override;
    std::vector<double> features() override;
    void removeDataBefore(time::Point time) override;

private:
    time::Series<int> sampleFlags;
};

}} // namespace elapse::coreplugin

#endif // DUMMYEEGFEATUREEXTRACTOR_H
