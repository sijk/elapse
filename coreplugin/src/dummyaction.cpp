#include <QxtLogger>
#include "dummyaction.h"


/*!
 * Create a new DummyAction.
 */
DummyAction::DummyAction()
{
}

/*!
 * Ignore the received \a state.
 */
void DummyAction::onState(elapse::data::CognitiveState state)
{
    Q_UNUSED(state)
    qxtLog->debug("Updated cognitive state");
}

