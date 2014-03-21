#include <QxtLogger>
#include <QPainter>
#include <qwt_dial.h>
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>
#include "batterymonitor.h"


/*!
 * \brief The DialWithSector class is a QwtDial with a coloured sector between
 * the lowerBound() and the sectorBound.
 */

class DialWithSector : public QwtDial
{
public:
    void setSectorBound(double value) { sectorBound = value; }

protected:
    void drawScaleContents(QPainter *painter,
                           const QPointF &center, double radius) const
    {
        Q_UNUSED(center)
        Q_UNUSED(radius)

        double startAngle = origin() + minScaleArc();
        double spanAngle = (sectorBound - lowerBound()) /
                           (upperBound() - lowerBound()) *
                           (maxScaleArc() - minScaleArc());

        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(Qt::red));
        painter->drawPie(scaleInnerRect(), startAngle * -16, spanAngle * -16);
        painter->restore();
    }

private:
    double sectorBound;
};


BatteryMonitor::BatteryMonitor(QObject *parent) :
    QObject(parent),
    battery(nullptr)
{
    gauge = new DialWithSector;
    gauge->setReadOnly(true);
    gauge->setOrigin(150);
    gauge->setScaleArc(0, 240);
    gauge->setLineWidth(2);
    gauge->setLowerBound(3.0);
    gauge->setUpperBound(4.0);
    gauge->setScaleMaxMajor(8);
    gauge->scaleDraw()->enableComponent(QwtRoundScaleDraw::Backbone, false);
    gauge->setNeedle(new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow));

    connect(&timer, SIGNAL(timeout()), SLOT(updateVoltage()));
}

QWidget *BatteryMonitor::getWidget()
{
    return gauge;
}

void BatteryMonitor::setBattery(org::nzbri::elapse::Battery *battery)
{
    this->battery = battery;
    if (!battery) {
        timer.stop();
        return;
    }

    gauge->setLowerBound(battery->criticalThresh());
    gauge->setSectorBound(battery->lowThresh());

    timer.start(1000);
}

void BatteryMonitor::updateVoltage()
{
    Q_ASSERT(battery);

    double voltage = battery->voltage();

    if (voltage > gauge->upperBound())
        gauge->setUpperBound(voltage);

    gauge->setValue(voltage);
}

