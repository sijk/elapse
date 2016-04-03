/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

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
