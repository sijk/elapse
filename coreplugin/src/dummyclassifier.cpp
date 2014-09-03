#include <QxtLogger>
#include "dummyclassifier.h"

namespace elapse { namespace coreplugin {

using elapse::data::FeatureVector;
using elapse::data::CognitiveState;


/*!
 * Create a new DummyClassifier.
 */
DummyClassifier::DummyClassifier()
{
}

CognitiveState DummyClassifier::classify(QList<FeatureVector> featureVectors)
{
    qxtLog->debug() << "Classify cognitive state";

    CognitiveState cog(featureVectors.first().startTime);
    cog.state = { 1.0 };
    return cog;
}

}} // namespace elapse::coreplugin
