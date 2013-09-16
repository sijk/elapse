#include <cmath>
#include "sineprovider.h"

SineProvider::SineProvider(QObject *parent) :
    DataProvider(parent),
    t(this)
{
    connect(&t, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void SineProvider::start()
{
    onTimer();
    t.start(40);
}

void SineProvider::stop()
{
    t.stop();
}

void SineProvider::onTimer()
{
    static double x;
    x = std::fmod(x + 0.1, 2 * M_PI);
    double y = std::sin(x);

    emit dataReady(y);
}
