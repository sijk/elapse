#include "ratelimiter.h"

namespace elapse { namespace widgets {

/*!
 * Create a RateLimiter as a child of the given \a parent which will emit
 * ready() at a maximum rate of \a hz.
 */
RateLimiter::RateLimiter(int hz, QObject *parent) :
    QObject(parent),
    hz(hz),
    ticked(false)
{
}

/*!
 * \return the maximum rate at which ready() will be emitted in Hz.
 */
int RateLimiter::rate() const
{
    return hz;
}

/*!
 * \fn RateLimiter::ready()
 * Output event.
 */

/*!
 * Input event.
 */
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
