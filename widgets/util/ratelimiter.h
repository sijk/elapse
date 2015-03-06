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
