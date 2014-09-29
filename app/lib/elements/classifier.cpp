#include <iterator>
#include <QxtLogger>
#include "elapse/timestamps.h"
#include "elapse/elements/classifier.h"

using elapse::data::Signal;


void elapse::elements::BaseClassifier::onFeatures(elapse::data::FeatureVector featVect)
{
    Q_ASSERT(featVect.startTime > 0);

    // Ensure we're not adding a FeatureVector to a feature set that was
    // previously removed for being incomplete
    auto firstSet = timestampedFeatureSets.cbegin();
    auto lastSet = timestampedFeatureSets.cend();
    Q_ASSERT((firstSet != lastSet)
             ? (featVect.startTime >= firstSet->first)
             : true);

    // Add the current feature vector to the queue
    FeatureSet &featureSet = timestampedFeatureSets[featVect.startTime];
    Q_ASSERT(!featureSet.contains(featVect.signalType));
    featureSet.insert(featVect.signalType, featVect);

    // If we have a complete set of feature vectors for this time point...
    if (featureSet.size() == Signal::count()) {
        // If there are incomplete feature sets from windows earlier
        // than the current one, assume they'll remain forever incomplete
        // and remove them.
        // TODO: figure out how this happens...
        auto first = timestampedFeatureSets.begin();
        auto current = timestampedFeatureSets.find(featVect.startTime);
        if (first != current) {
            qxtLog->debug() << "Removing" << (int)std::distance(first, current)
                            << "incomplete feature sets before complete set at"
                            << elapse::time::format(current->first);

            while (first != current)
                first = timestampedFeatureSets.erase(first);
        }

        // Analyse the feature set
        emit newState(classify(featureSet.values()));
        timestampedFeatureSets.erase(featVect.startTime);

        qxtLog->debug() << (uint)timestampedFeatureSets.size()
                        << "partial feature sets pending";
    }
}

void elapse::elements::BaseClassifier::reset()
{
    timestampedFeatureSets.clear();
}

