/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QObject>
#include <set>
#include "elapse/datatypes.h"
#include "elapse/timestamps.h"

namespace elapse { namespace elements {

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
    virtual void onFeatures(elapse::data::FeatureVector::const_ptr features) = 0;

    /*!
     * Called when the pipeline starts to reset any internal state.
     */
    virtual void reset() = 0;

signals:
    /*!
     * Emitted when the CognitiveState has been classified from the latest
     * set of FeatureVector%s.
     */
    void newState(elapse::data::CognitiveState::const_ptr state);
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
    void onFeatures(elapse::data::FeatureVector::const_ptr featVect) override;
    void reset() override;

protected:
    using FeatureSet = std::set<data::FeatureVector::const_ptr>;

    /*!
     * Derived classes should implement this method to classify the user's
     * current CognitiveState given the list of \a featureVectors.
     */
    virtual std::vector<double> classify(const FeatureSet &featureVectors) = 0;

private:
    time::Series<FeatureSet> timestampedFeatureSets;
};

}} // namespace elapse::elements

#endif // CLASSIFIER_H
