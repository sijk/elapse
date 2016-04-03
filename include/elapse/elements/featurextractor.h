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

#ifndef FEATUREXTRACTOR_H
#define FEATUREXTRACTOR_H

#include <QObject>
#include <QScopedPointer>
#include "elapse/datatypes.h"
#include "elapse/timestamps.h"

namespace elapse { namespace elements {

/*!
 * \brief The FeatureExtractor interface is implemented by elements that
 * analyse a time series of Sample%s to extract a FeatureVector.
 *
 * Each Pipeline has several FeatureExtractor%s: one per Signal::Type.
 *
 * \note To implement a FeatureExtractor, inherit from BaseFeatureExtractor.
 *
 * \headerfile elapse/elements/featurextractor.h
 * \ingroup pipeline-elements
 */

class FeatureExtractor : public QObject
{
    Q_OBJECT

public:
    /*! Set the \a timestamp at which the first window begins. */
    virtual void setStartTime(time::Point timestamp) = 0;

    /*! Set the length of each window in \a ms. */
    virtual void setWindowLength(uint ms) = 0;

    /*! Set the time between the beginning of adjacent windows in \a ms. */
    virtual void setWindowStep(uint ms) = 0;

    /*! Configure this FeatureExtractor to match the given hardware \a config. */
    virtual void configure(QMap<QString, QVariantMap> config) { Q_UNUSED(config); }

public slots:
    /*! Executed when the next \a sample is available for analysis. */
    virtual void onSample(elapse::data::SamplePtr sample) = 0;

signals:
    /*! Emitted when a complete window has been analysed. */
    void newFeatures(elapse::data::FeatureVector::const_ptr features);
};


class BaseFeatureExtractorPrivate;

/*!
 * \brief The BaseFeatureExtractor class provides a base implementation of a
 * generic feature extractor that handles most of the windowing logic
 * internally.
 *
 * To implement a FeatureExtractor, inherit from this class and implement the
 * protected virtual methods.
 *
 * The windowing implementation provided by this class should be sufficient for
 * most FeatureExtractors. If you really need to, you may inherit directly from
 * FeatureExtractor, but you \b must make sure that the windowing behaviour is
 * identical to that implemented here.
 *
 * \headerfile elapse/elements/featurextractor.h
 * \ingroup pipeline-elements
 */

class BaseFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT

public:
    BaseFeatureExtractor();
    ~BaseFeatureExtractor();

    void setStartTime(time::Point timestamp) override;

    void setWindowLength(uint length) override;
    void setWindowStep(uint step) override;

public slots:
    void onSample(elapse::data::SamplePtr sample) override;

protected:
    /*!
     * Derived classes should implement this method to analyse the given
     * \a sample. The result will need to be stored internally until the
     * next call to features().
     * \sa time::Series for a convenient data structure to store the
     * results of this analysis.
     */
    virtual void analyseSample(data::SamplePtr sample) = 0;

    /*!
     * \return a list of features calculated from the previously analysed
     * Sample%s in the current window.
     */
    virtual std::vector<double> features() = 0;

    /*!
     * Remove any internal data that is related to samples occurring before
     * the given \a time.
     */
    virtual void removeDataBefore(time::Point time) = 0;

    /*!
     * Reset any internal state. Defaults to calling removeDataBefore() with
     * the maximum value a time::Point can hold.
     */
    virtual void reset();

    /*!
     * \return the data::Signal::Type with which this FeatureExtractor
     * operates. Defaults to the value of the Q_CLASSINFO("SignalType") field.
     */
    virtual data::Signal::Type signalType() const;

private:
    const QScopedPointer<BaseFeatureExtractorPrivate> d_ptr;
    Q_DECLARE_PRIVATE(BaseFeatureExtractor)
};

}} // namespace elapse::elements

#endif // FEATUREXTRACTOR_H
