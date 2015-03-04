#ifndef RATELIMITER_H
#define RATELIMITER_H

#include <QObject>
#include <QBasicTimer>

namespace elapse { namespace widgets {

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
