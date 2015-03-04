#include "ratelimiter.h"

namespace elapse { namespace widgets {

RateLimiter::RateLimiter(int hz, QObject *parent) :
    QObject(parent),
    hz(hz),
    ticked(false)
{
}

int RateLimiter::rate() const
{
    return hz;
}

void RateLimiter::operator()()
{
    Q_ASSERT(hz != 0);

    bool wasInactive = !ticked;
    ticked = true;

    if (!timer.isActive()) {
        if (wasInactive)
            timerEvent(nullptr);
        timer.start(1000 / hz, this);
    }
}

void RateLimiter::timerEvent(QTimerEvent *)
{
    if (!ticked) {
        timer.stop();
        return;
    }

    emit ready();

    ticked = false;
}

}} // namespace elapse::widgets
