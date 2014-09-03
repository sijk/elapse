#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QObject>
#include "elapse/sampletypes.h"
#include "elapse/timestamps.h"

namespace elapse {

/*!
 * \brief The Classifier interface is implemented by elements that take in
 * FeatureVector%s and classify the CognitiveState of the device user.
 *
 * Each Pipeline has one Classifier.
 *
 * \note To implement a Classifier, inherit from BaseClassifier.
 *
 * \headerfile elapse/elements/classifier.h
 * \ingroup pipeline-elements
 */

class Classifier : public QObject
{
    Q_OBJECT

public slots:
    /*!
     * Called when \a features are available for classification. This slot will
     * be called by each FeatureExtractor, and it is the responsibility of
     * Classifier subclasses to match up and process the corresponding
     * FeatureVector%s.
     */
    virtual void onFeatures(elapse::data::FeatureVector features) = 0;

    /*!
     * Called when the pipeline starts to reset any internal state.
     */
    virtual void reset() = 0;

signals:
    /*!
     * Emitted when the CognitiveState has been classified from the latest
     * set of FeatureVector%s.
     */
    void newState(elapse::data::CognitiveState state);
};


/*!
 * \brief The BaseClassifier class provides a base implementation of a generic
 * classifier that takes care of aggregating related FeatureVector%s internally.
 *
 * To implement a BaseClassifier, inherit from this class and implement
 * classify(). It is possible to inherit directly from Classifier, though
 * this should be unnecessary and if you do it you must ensure the onFeatures
 * signals are handled correctly.
 *
 * \headerfile elapse/elements/classifier.h
 * \ingroup pipeline-elements
 */

class BaseClassifier : public Classifier
{
    Q_OBJECT

public slots:
    void onFeatures(elapse::data::FeatureVector featVect);
    void reset();

protected:
    /*!
     * Derived classes should implement this method to classify the user's
     * current CognitiveState given the list of \a featureVectors.
     */
    virtual data::CognitiveState classify(QList<data::FeatureVector> featureVectors) = 0;

private:
    typedef QMap<data::Signal::Type, data::FeatureVector> FeatureSet;
    time::Series<FeatureSet> timestampedFeatureSets;
};

} // namespace elapse

#endif // CLASSIFIER_H
