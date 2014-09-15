#include <QxtLogger>
#include "dummyaction.h"

namespace elapse { namespace coreplugin {

/*!
 * Create a new DummyAction.
 */
DummyAction::DummyAction()
{
}

/*!
 * Ignore the received \a state.
 */
void DummyAction::onState(data::CognitiveState state)
{
    Q_UNUSED(state)
    qxtLog->debug("Updated cognitive state");
}

}} // namespace elapse::coreplugin
