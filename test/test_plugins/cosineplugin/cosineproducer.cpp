#include <cmath>
#include "cosineproducer.h"

CosineProducer::CosineProducer(QObject *parent) :
    Producer(parent),
    t(this)
{
    connect(&t, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void CosineProducer::start()
{
    onTimer();
    t.start(40);
}

void CosineProducer::stop()
{
    t.stop();
}

void CosineProducer::onTimer()
{
    static double x;
    x = std::fmod(x + 0.1, 2 * M_PI);
    double y = std::cos(x);

    emit dataReady(y);
}
