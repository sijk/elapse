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
