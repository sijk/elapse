#include <cmath>
#include "cosineprovider.h"

CosineProvider::CosineProvider(QObject *parent) :
    DataProvider(parent),
    t(this)
{
    connect(&t, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void CosineProvider::start()
{
    onTimer();
    t.start(40);
}

void CosineProvider::stop()
{
    t.stop();
}

void CosineProvider::onTimer()
{
    static double x;
    x = std::fmod(x + 0.1, 2 * M_PI);
    double y = std::cos(x);

    emit dataReady(y);
}
