#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QObject>
#include "elapse/sampletypes.h"

namespace elapse {

/*!
 * \brief The Classifier class is the base class for elements that take in
 * FeatureVector%s and classify the CognitiveState of the device user.
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

public slots:
    /*!
     * Called when \a features are available for classification. This slot will
     * be called by each FeatureExtractor, and it is the responsibility of
     * Classifier subclasses to match up and process the corresponding
     * FeatureVector%s.
     */
    virtual void onFeatures(FeatureVector features) = 0;

signals:
    /*!
     * Emitted when the CognitiveState has been classified from the latest
     * set of FeatureVector%s.
     */
    void newState(CognitiveState state);
};

} // namespace elapse

#endif // CLASSIFIER_H
