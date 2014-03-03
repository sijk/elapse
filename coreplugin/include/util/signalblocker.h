#ifndef SIGNALBLOCKER_H
#define SIGNALBLOCKER_H

#include <QObject>

/*
 *  Use RAII to un/block signals.
 */

class SignalBlocker
{
public:
    SignalBlocker(QObject *obj) :
        obj(obj)
    {
        wasBlocked = obj->blockSignals(true);
    }

    ~SignalBlocker()
    {
        obj->blockSignals(wasBlocked);
    }

private:
    QObject* const obj;
    bool wasBlocked;
};

#endif // SIGNALBLOCKER_H
