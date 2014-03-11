#ifndef FEATUREXTRACTOR_H
#define FEATUREXTRACTOR_H

#include <QObject>
#include "sampletypes.h"


/*!
 * \brief The FeatureExtractor class is the base class for elements that
 * analyse a time series of Sample%s to extract a FeatureVector.
 *
 * Each Pipeline has several FeatureExtractor%s: one per Signal::Type.
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
    virtual void onSample(SamplePtr sample) = 0;

signals:
    /*! Emitted when a complete window has been analysed. */
    void newFeatures(FeatureVector features);
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
    /*! Create a BaseFeatureExtractor as a child of the given \a parent. */
    explicit BaseFeatureExtractor(QObject *parent = nullptr) :
        FeatureExtractor(parent), windowStart(0), signalType(Signal::INVALID)
    { }

    void setStartTime(quint64 timestamp)
    {
        windowStart = timestamp;
        signalType = findSignalType();
    }

    void setWindowLength(uint ms) { windowLength = ms; }
    void setWindowStep(uint ms) { windowStep = ms; }

public slots:
    /*!
     * Handle the given \a sample. This method takes care of updating the
     * window as necessary and delegates the actual feature extraction to
     * the protected methods.
     */
    void onSample(SamplePtr sample)
    {
        if (windowStart == 0)
            return;
        Q_ASSERT(signalType != Signal::INVALID);

        if (sample->timestamp < windowStart)
            return;

        quint64 windowEnd = windowStart + windowLength * 1e6;
        quint64 nextWindowStart = windowStart + windowStep * 1e6;

        if (sample->timestamp >= windowEnd) {
            emit newFeatures({signalType, windowStart, features()});
            removeDataBefore(nextWindowStart);
            windowStart = nextWindowStart;
        }
        analyseSample(sample);
    }

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

private:
    quint64 windowStart;
    uint windowLength;
    uint windowStep;
    Signal::Type signalType;

    /*!
     * \return the Signal::Type this FeatureExtractor works with, as defined
     * by the "SignalType" class info field.
     */
    Signal::Type findSignalType() const
    {
        const int index = metaObject()->indexOfClassInfo("SignalType");
        const char *info = metaObject()->classInfo(index).value();
        return Signal::fromString(info);
    }
};

#endif // FEATUREXTRACTOR_H
