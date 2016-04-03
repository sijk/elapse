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

#include <iterator>
#include <QxtLogger>
#include "elapse/timestamps.h"
#include "elapse/elements/classifier.h"

namespace elapse { namespace elements {

void BaseClassifier::onFeatures(data::FeatureVector::const_ptr featVect)
{
    const time::Point timestamp = featVect->startTime;
    Q_ASSERT(timestamp > 0);

#ifdef Q_DEBUG
    // Ensure we're not adding a FeatureVector to a feature set that was
    // previously removed for being incomplete
    auto firstSet = timestampedFeatureSets.cbegin();
    auto lastSet = timestampedFeatureSets.cend();
    if (firstSet != lastSet)
        Q_ASSERT(timestamp >= firstSet->first);
#endif

    // Add the current feature vector to the queue
    FeatureSet &featureSet = timestampedFeatureSets[timestamp];
    Q_ASSERT(std::none_of(featureSet.cbegin(), featureSet.cend(),
             [&](const data::FeatureVector::const_ptr &existing){
                 return featVect->signalType == existing->signalType;
             }));
    featureSet.insert(featVect);

    // If we have a complete set of feature vectors for this time point...
    if (featureSet.size() == data::Signal::count()) {
#ifdef Q_DEBUG
        // If there are incomplete feature sets from windows earlier
        // than the current one, assume they'll remain forever incomplete
        // and remove them.
        // TODO: figure out how this happens...
        auto first = timestampedFeatureSets.begin();
        auto current = timestampedFeatureSets.find(timestamp);
        if (first != current) {
            qxtLog->debug() << "Removing" << (int)std::distance(first, current)
                            << "incomplete feature sets before complete set at"
                            << time::format(current->first);

            while (first != current)
                first = timestampedFeatureSets.erase(first);
        }
#endif

        // Analyse the feature set
        auto cognitiveState = std::make_shared<data::CognitiveState>(timestamp);
        cognitiveState->state = classify(featureSet);
        emit newState(cognitiveState);
        timestampedFeatureSets.erase(timestamp);

#ifdef Q_DEBUG
        auto pending = timestampedFeatureSets.size();
        if (pending > 0)
            qxtLog->debug() << (uint)pending << "partial feature sets pending";
#endif
    }
}

void BaseClassifier::reset()
{
    timestampedFeatureSets.clear();
}

}} // namespace elapse::elements

