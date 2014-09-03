#ifndef OUTPUTACTION_H
#define OUTPUTACTION_H

#include <QObject>
#include "elapse/datatypes.h"

namespace elapse {

/*!
 * \brief The OutputAction interface is implemented by elements that perform
 * some action based on the classified CognitiveState.
 *
 * Each Pipeline has one OutputAction.
 * \todo It should be possible to have a set of OutputAction%s that get
 * executed in parallel.
 *
 * \headerfile elapse/elements/outputaction.h
 * \ingroup pipeline-elements
 */

class OutputAction : public QObject
{
    Q_OBJECT

public slots:
    /*!
     * Called when \a features are available for classification. This slot will
     * be called by each FeatureExtractor, and it is the responsibility of
     * OutputAction subclasses to match up and process the corresponding
     * FeatureVector%s.
     */
    virtual void onState(elapse::data::CognitiveState state) = 0;
};

} // namespace elapse

#endif // OUTPUTACTION_H
