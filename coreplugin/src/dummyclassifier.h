#ifndef DUMMYCLASSIFIER_H
#define DUMMYCLASSIFIER_H

#include <elapse/elements/classifier.h>


/*!
 * \brief The DummyClassifier class is a black hole for FeatureVector%s.
 *
 * \ingroup core-plugin
 */

class DummyClassifier : public elapse::BaseClassifier
{
    Q_OBJECT
public:
    Q_INVOKABLE DummyClassifier();

protected:
    elapse::CognitiveState classify(QList<elapse::FeatureVector> featureVectors);
};

#endif // DUMMYCLASSIFIER_H
