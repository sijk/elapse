#ifndef FEATUREXTRACTOR_H
#define FEATUREXTRACTOR_H

#include <QObject>
#include "elapse/sampletypes.h"

namespace elapse {

/*!
 * \brief The FeatureExtractor interface is implemented by elements that
 * analyse a time series of Sample%s to extract a FeatureVector.
 *
 * Each Pipeline has several FeatureExtractor%s: one per Signal::Type.
 *
 * \note To implement a FeatureExtractor, inherit from BaseFeatureExtractor.
 *
 * \ingroup pipeline-elements
 */

class FeatureExtractor : public QObject
{
    Q_OBJECT

public:
    /*! Construct a new FeatureExtractor as a child of the given \a parent. */
    explicit FeatureExtractor(QObject *parent = nullptr) : QObject(parent) {}

    /*! Destroy this FeatureExtractor. */
    virtual ~FeatureExtractor() {}

    /*! Set the \a timestamp at which the first window begins. */
    virtual void setStartTime(quint64 timestamp) = 0;

    /*! Set the length of each window in \a ms. */
    virtual void setWindowLength(uint ms) = 0;

    /*! Set the time between the beginning of adjacent windows in \a ms. */
    virtual void setWindowStep(uint ms) = 0;

public slots:
    /*! Executed when the next \a sample is available for analysis. */
    virtual void onSample(elapse::SamplePtr sample) = 0;

signals:
    /*! Emitted when a complete window has been analysed. */
    void newFeatures(elapse::FeatureVector features);
};



/*!
 * \brief The BaseFeatureExtractor class provides a base implementation of a
 * generic feature extractor that handles most of the windowing logic
 * internally.
 *
 * The windowing implementation provided by this class should be sufficient for
 * most FeatureExtractors. If you really need to, you may inherit directly from
 * FeatureExtractor, but you \b must make sure that the windowing behaviour is
 * identical to that implemented here.
 */

class BaseFeatureExtractor : public FeatureExtractor
{
    Q_OBJECT
public:
    explicit BaseFeatureExtractor(QObject *parent = nullptr);

    void setStartTime(quint64 timestamp);

    void setWindowLength(uint ms);
    void setWindowStep(uint ms);

public slots:
    void onSample(elapse::SamplePtr sample);

protected:
    /*!
     * Derived classes should implement this method to analyse the given
     * \a sample. The result will need to be stored internally until the
     * next call to featureVector().
     * \sa TimestampedValues for a convenient data structure to store the
     * results of this analysis.
     */
    virtual void analyseSample(SamplePtr sample) = 0;

    /*!
     * \return a list of features calculated from the previously analysed
     * Sample%s in the current window.
     */
    virtual QVector<double> features() = 0;

    /*!
     * Remove any internal data that is related to samples occurring before
     * the given \a time.
     */
    virtual void removeDataBefore(quint64 time) = 0;

    /*!
     * Reset any internal state. Defaults to calling removeDataBefore() with
     * the maximum value a quint64 can hold.
     */
    virtual void reset();

private:
    quint64 windowStart;
    uint windowLength;
    uint windowStep;
    Signal::Type signalType;

    Signal::Type findSignalType() const;
};

} // namespace elapse

#endif // FEATUREXTRACTOR_H