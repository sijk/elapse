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

#ifndef RATELIMITER_H
#define RATELIMITER_H

#include <QObject>
#include <QBasicTimer>

namespace elapse { namespace widgets {

/*!
 * \brief The RateLimiter class provides a convenient way to limit events
 * to some maximum rate.
 *
 * Suppose we have something like the snippet below. The RateLimiter object
 * is initialised with the desired maximum rate, in this case 30 Hz. Its
 * ready() signal is connected to some slot, in this case, redrawing a widget.
 * Then, if update() is called at more than 30 Hz, widget->redraw() will only
 * be called at 30 Hz. If update() is called at < 30 Hz (e.g. 10 Hz),
 * widget->redraw() will be called at the same rate (10 Hz).
 *
 *      RateLimiter update(30);
 *      connect(&update, SIGNAL(ready()), widget, SLOT(redraw()));
 *      for (...) {
 *          ...
 *          update();
 *      }
 *
 * This class is used internally by some of the elapse::widgets, but is not
 * available for use by external (plugin) code.
 */
class RateLimiter : public QObject
{
    Q_OBJECT
public:
    explicit RateLimiter(int hz, QObject *parent = nullptr);
    int rate() const;
    void operator()();

signals:
    void ready();

private:
    QBasicTimer timer;
    int hz;
    bool ticked;

    void timerEvent(QTimerEvent *) override;
};

}} // namespace elapse::widgets

#endif // RATELIMITER_H
