#include <QxtLogger>
#include "dummyaction.h"


/*!
 * Create a new DummyAction as a child of the given \a parent.
 */
DummyAction::DummyAction(QObject *parent) :
    OutputAction(parent)
{
}

/*!
 * Ignore the received \a state.
 */
void DummyAction::onState(elapse::CognitiveState state)
{
    Q_UNUSED(state)
    qxtLog->debug("Updated cognitive state");
}

