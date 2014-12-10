#ifndef DIALWITHSECTOR_H
#define DIALWITHSECTOR_H

#include <qwt_dial.h>

namespace elapse { namespace widgets {

/*!
 * \brief The DialWithSector class is a QwtDial with a coloured sector between
 * the lowerBound() and the sectorBound.
 */

class DialWithSector : public QwtDial
{
    Q_OBJECT
public:
    explicit DialWithSector(QWidget *parent = nullptr);
    void setSectorBound(double value);

protected:
    void drawScaleContents(QPainter *painter,
                           const QPointF &center, double radius) const override;

private:
    double sectorBound;
};

}} // namespace elapse::widgets

#endif // DIALWITHSECTOR_H
