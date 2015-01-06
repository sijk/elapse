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

