#ifndef DUMMYACTION_H
#define DUMMYACTION_H

#include <elapse/elements/outputaction.h>


/*!
 * \brief The DummyAction class is a black hole for elapse::CognitiveState%s.
 *
 * \ingroup core-plugin
 */

class DummyAction : public elapse::elements::OutputAction
{
    Q_OBJECT
public:
    Q_INVOKABLE DummyAction();

public slots:
    void onState(elapse::data::CognitiveState state);
};

#endif // DUMMYACTION_H
