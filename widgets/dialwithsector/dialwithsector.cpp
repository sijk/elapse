#include <QPainter>
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>
#include "dialwithsector.h"


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


namespace elapse { namespace widgets {

DialWithSector::DialWithSector(QWidget * parent) :
    QwtDial(parent),
    sectorBound((upperBound() - lowerBound()) / 2)
{
    setReadOnly(true);
    setOrigin(150);
    setScaleArc(0, 240);
    setLineWidth(2);
    setScaleMaxMajor(8);
    setScaleDraw(new CompactRoundScaleDraw);
    setNeedle(new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow));
}

/*!
 * Set the upper bound of the sector to \a value.
 */
void DialWithSector::setSectorBound(double value)
{
    sectorBound = value;
}

void DialWithSector::drawScaleContents(QPainter *painter, const QPointF &center,
                                       double radius) const
{
    Q_UNUSED(center);
    Q_UNUSED(radius);

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

}} // namespace elapse::widgets

