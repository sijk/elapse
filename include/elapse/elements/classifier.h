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

    /*!
     * Called when the pipeline starts to reset any internal state.
     */
    virtual void reset() = 0;

signals:
    /*!
     * Emitted when the CognitiveState has been classified from the latest
     * set of FeatureVector%s.
     */
    void newState(CognitiveState state);
};


/*!
 * \brief The BaseClassifier class provides a base implementation of a generic
 * classifier that takes care of aggregating related FeatureVector%s internally.
 *
 * To implement a BaseClassifier, inherit from this class and implement
 * classify(). It is possible to inherit directly from Classifier, though
 * this should be unnecessary and if you do it you must ensure the onFeatures
 * signals are handled correctly.
 */

class BaseClassifier : public Classifier
{
    Q_OBJECT
public:
    /*! Construct a new BaseClassifier as a child of the given \a parent. */
    explicit BaseClassifier(QObject *parent = nullptr) : Classifier(parent) {}

public slots:
    void onFeatures(FeatureVector featVect)
    {
        Q_ASSERT(featVect.startTime > 0);

        // Ensure we're not adding a FeatureVector to a feature set that was
        // previously removed for being incomplete
        auto firstSet = timestampedFeatureSets.constBegin();
        auto lastSet = timestampedFeatureSets.constEnd();
        Q_ASSERT((firstSet != lastSet)
                 ? (featVect.startTime >= firstSet.key())
                 : true);

        // Add the current feature vector to the queue
        FeatureSet &featureSet = timestampedFeatureSets[featVect.startTime];
        Q_ASSERT(!featureSet.contains(featVect.signalType));
        featureSet.insert(featVect.signalType, featVect);

        // If we have a complete set of feature vectors for this time point...
        if (featureSet.size() == Signal::count()) {
            // If there are incomplete feature sets from windows earlier
            // than the current one, assume they'll remain forever incomplete
            // and remove them.
            auto first = timestampedFeatureSets.begin();
            auto current = timestampedFeatureSets.find(featVect.startTime);
            while (first != current)
                first = timestampedFeatureSets.erase(first);

            // Analyse the feature set
            emit newState(classify(featureSet.values()));
            timestampedFeatureSets.remove(featVect.startTime);
        }
    }

    void reset()
    {
        timestampedFeatureSets.clear();
    }

protected:
    /*!
     * Derived classes should implement this method to classify the user's
     * current CognitiveState given the list of \a featureVectors.
     */
    virtual CognitiveState classify(QList<FeatureVector> featureVectors) = 0;

private:
    typedef QMap<Signal::Type, FeatureVector> FeatureSet;
    QMap<quint64, FeatureSet> timestampedFeatureSets;
};

} // namespace elapse

#endif // CLASSIFIER_H
