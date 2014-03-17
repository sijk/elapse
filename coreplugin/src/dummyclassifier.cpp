#include "dummyclassifier.h"

using elapse::FeatureVector;
using elapse::CognitiveState;


DummyClassifier::DummyClassifier(QObject *parent) :
    Classifier(parent)
{
}

void DummyClassifier::onFeatures(FeatureVector features)
{
    Q_UNUSED(features)
}
