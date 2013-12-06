#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QObject>


/*!
 * \brief The Classifier class is the base class for elements that take in one
 * or more FeatureVectors and classify the CognitiveState of the device user.
 *
 * Each Pipeline has one Classifier.
 *
 * \ingroup pipeline-elements
 */

class Classifier : public QObject
{
    Q_OBJECT

public:
    /*! Construct a new Classifier as a child of the given \a parent. */
    explicit Classifier(QObject *parent = nullptr) : QObject(parent) {}

    /*! Destroy this Classifier. */
    virtual ~Classifier() {}
};

#endif // CLASSIFIER_H
