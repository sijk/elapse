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

#ifndef STRIPCHART_H
#define STRIPCHART_H

#include <QWidget>
#include <QScopedPointer>

namespace elapse { namespace widgets {

class StripChartPrivate;

/*!
 * \brief The StripChart class provides a generic stripchart widget for
 * displaying time-series data.
 *
 * Redrawing is handled intelligently. If calls to appendData() occur less than
 * \c rate milliseconds apart, the plot will be drawn every \c rate
 * milliseconds. If appendData() calls occur more than \c rate milliseconds
 * apart, the plot will be redrawn on each appendData() call. If appendData()
 * is not called, the plot is not redrawn. This approach minimises computation
 * while ensuring display responsiveness.
 *
 * \see RateLimiter
 * \headerfile elapse/widgets/stripchart.h
 * \ingroup widgets
 */

class StripChart : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(uint nStrips READ nStrips WRITE setNStrips)
    Q_PROPERTY(uint nSamples READ nSamples WRITE setNSamples)
    Q_PROPERTY(double stripSpacing READ spacing WRITE setSpacing)
    Q_PROPERTY(bool demean READ demean WRITE setDemean)
    Q_PROPERTY(uint rate READ rate)

public:
    explicit StripChart(QWidget *parent = nullptr);
    ~StripChart();

public slots:
    void appendData(const std::vector<double> &data);

    uint nStrips() const;
    void setNStrips(uint n);

    uint nSamples() const;
    void setNSamples(uint n);

    double spacing() const;
    void setSpacing(double spacing);
    void setSpacing(int spacing) { setSpacing(double(spacing)); }

    bool demean() const;
    void setDemean(bool demean);

    uint rate() const;

private:
    const QScopedPointer<StripChartPrivate> d_ptr;
    Q_DECLARE_PRIVATE(StripChart)
};

}} // namespace elapse::widgets

#endif // STRIPCHART_H
