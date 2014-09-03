#include <QxtLogger>
#include <QPainter>
#include <qwt_dial.h>
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>
#include "common/hardware/battery_iface.h"
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


/*!
 * \brief The CompactRoundScaleDraw class is a QwtRoundScaleDraw tweaked to
 * take up less space.
 */

class CompactRoundScaleDraw : public QwtRoundScaleDraw
{
public:
    CompactRoundScaleDraw() : QwtRoundScaleDraw()
    {
        enableComponent(QwtAbstractScaleDraw::Backbone, false);
        setTickLength(QwtScaleDiv::MinorTick, 3);
        setTickLength(QwtScaleDiv::MediumTick, 4);
        setTickLength(QwtScaleDiv::MajorTick, 5);
        setSpacing(2);
    }

protected:
    QwtText label(double value) const
    {
        QwtText text = QwtRoundScaleDraw::label(value);
        QFont font = text.font();
        font.setPixelSize(10);
        text.setFont(font);
        return text;
    }
};


namespace elapse { namespace client {

/*!
 * Create a BatteryMonitor as a child of the given \a parent.
 */
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
    gauge->setScaleDraw(new CompactRoundScaleDraw);
    gauge->setNeedle(new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow));

    connect(&timer, SIGNAL(timeout()), SLOT(updateVoltage()));
}

/*!
 * \return the battery voltage gauge widget.
 */
QWidget *BatteryMonitor::getWidget()
{
    return gauge;
}

/*!
 * Set the DBus interface to the device's \a battery.
 */
void BatteryMonitor::setBattery(hardware::Battery *battery)
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

/*!
 * Read the battery voltage from the device and display it on the gauge.
 */
void BatteryMonitor::updateVoltage()
{
    Q_ASSERT(battery);

    double voltage = battery->voltage();

    if (voltage > gauge->upperBound())
        gauge->setUpperBound(voltage);

    gauge->setValue(voltage);
}

}} // namespace elapse::client
