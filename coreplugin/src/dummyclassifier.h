#ifndef DUMMYCLASSIFIER_H
#define DUMMYCLASSIFIER_H

#include <elapse/elements/classifier.h>


/*!
 * \brief The DummyClassifier class is a black hole for FeatureVectors.
 *
 * \ingroup core-plugin
 */

class DummyClassifier : public elapse::Classifier
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DummyClassifier(QObject *parent = nullptr);

public slots:
    void onFeatures(elapse::FeatureVector features);
};

#endif // DUMMYCLASSIFIER_H
