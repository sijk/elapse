#ifndef FEATUREXTRACTOR_H
#define FEATUREXTRACTOR_H

#include <QObject>
#include "sampletypes.h"


/*!
 * \brief The FeatureExtractor class is the base class for elements that
 * analyse a time series of Sample%s to extract a FeatureVector.
 *
 * Each Pipeline has several FeatureExtractor%s: one per \ref SampleType.
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

#endif // FEATUREXTRACTOR_H
