#include <QxtLogger>
#include "dummyclassifier.h"

using elapse::FeatureVector;
using elapse::CognitiveState;


/*!
 * Create a new DummyClassifier as a child of the given \a parent.
 */
DummyClassifier::DummyClassifier(QObject *parent) :
    BaseClassifier(parent)
{
}

CognitiveState DummyClassifier::classify(QList<FeatureVector> featureVectors)
{
    qxtLog->debug() << "Classify cognitive state";

    CognitiveState cog(featureVectors.first().startTime);
    cog.state = { 1.0 };
    return cog;
}
