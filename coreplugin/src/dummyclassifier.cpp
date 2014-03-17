#include "dummyclassifier.h"

DummyClassifier::DummyClassifier(QObject *parent) :
    Classifier(parent)
{
}

void DummyClassifier::onFeatures(FeatureVector features)
{
    Q_UNUSED(features)
}
