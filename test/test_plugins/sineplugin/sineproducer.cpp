#include <cmath>
#include "sineproducer.h"

SineProducer::SineProducer(QObject *parent) :
    Producer(parent),
    t(this)
{
    connect(&t, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void SineProducer::start()
{
    onTimer();
    t.start(40);
}

void SineProducer::stop()
{
    t.stop();
}

void SineProducer::onTimer()
{
    static double x;
    x = std::fmod(x + 0.1, 2 * M_PI);
    double y = std::sin(x);

    emit dataReady(y);
}
