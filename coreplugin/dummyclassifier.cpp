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
#include "dummyclassifier.h"

namespace elapse { namespace coreplugin {

using data::FeatureVector;
using data::CognitiveState;


/*!
 * Create a new DummyClassifier.
 */
DummyClassifier::DummyClassifier()
{
}

std::vector<double> DummyClassifier::classify(const FeatureSet &featureVectors)
{
    Q_UNUSED(featureVectors);
    qxtLog->debug() << "Classify cognitive state";
    return { 1.0 };
}

}} // namespace elapse::coreplugin
