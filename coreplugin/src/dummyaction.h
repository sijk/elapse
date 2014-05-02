#ifndef DUMMYACTION_H
#define DUMMYACTION_H

#include <elapse/elements/outputaction.h>


/*!
 * \brief The DummyAction class is a black hole for elapse::CognitiveState%s.
 *
 * \ingroup core-plugin
 */

class DummyAction : public elapse::OutputAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DummyAction(QObject *parent = nullptr);

public slots:
    void onState(elapse::CognitiveState state);
};

#endif // DUMMYACTION_H
