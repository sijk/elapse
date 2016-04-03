/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef DIALWITHSECTOR_H
#define DIALWITHSECTOR_H

#include <qwt_dial.h>

namespace elapse { namespace widgets {

/*!
 * \brief The DialWithSector class is a QwtDial with a coloured sector between
 * the lowerBound() and the sectorBound.
 *
 * \headerfile elapse/widgets/dialwithsector.h
 * \ingroup widgets
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
