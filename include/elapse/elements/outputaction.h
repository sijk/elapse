#ifndef OUTPUTACTION_H
#define OUTPUTACTION_H

#include <QObject>
#include "elapse/datatypes.h"

namespace elapse { namespace elements {

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
     * Take some action based on the user's cognitive \a state.
     */
    virtual void onState(elapse::data::CognitiveState::const_ptr state) = 0;
};

}} // namespace elapse::elements

#endif // OUTPUTACTION_H
