#include <memory>
#include <QTimer>
#include <QVBoxLayout>
#include <QxtLogger>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include "stripchart.h"


namespace {

const QList<QColor> lineColours = {
    Qt::red, Qt::yellow, Qt::green, Qt::cyan, Qt::blue, Qt::magenta,
};


/*!
 * \brief The StripChartScaleDraw class labels the y-axis of a StripChart.
 *
 * Labels are of the format "Ch n" where n is the strip index.
 */
class StripChartScaleDraw : public QwtScaleDraw
{
public:
    StripChartScaleDraw(double spacing) : QwtScaleDraw(), space(spacing) {}

    QwtText label(double value) const
    {
        return QStringLiteral("Ch %1").arg(int(-value / space));
    }

private:
    double space;
};

} // namespace

namespace elapse { namespace widgets {

class StripChartPrivate
{
    StripChart * const q_ptr;
    Q_DECLARE_PUBLIC(StripChart)
public:
    StripChartPrivate(StripChart *q);

    void redraw();
    void createStrips();

    QVBoxLayout *layout;
    QwtPlot *plot;
    std::vector<std::unique_ptr<QwtPlotCurve>> lines;
    QVector<double> tdata;
    QList<QVector<double>> ydata;

    uint nStrips;
    uint nSamples;
    double spacing;
    uint rate;

    QTimer *timer;
    bool needsRedraw;
};


StripChartPrivate::StripChartPrivate(StripChart *q) :
    q_ptr(q),
    plot(new QwtPlot(q)),
    nStrips(1),
    nSamples(100),
    spacing(1.0),
    rate(10),
    timer(new QTimer(q))
{
    // Create a layout and add the plot
    layout = new QVBoxLayout(q);
    layout->addWidget(plot);

    plot->setCanvasBackground(Qt::white);

    QObject::connect(timer, &QTimer::timeout, [this]{ redraw(); });
}

/*!
 * Helper function to set up the QwtPlotCurves, axis labels, and so on given the
 * current configuration.
 */
void StripChartPrivate::createStrips()
{
    Q_Q(StripChart);

    // Delete any existing lines
    lines.clear();
    ydata.clear();

    lines.reserve(nStrips);
    tdata.resize(nSamples);
    ydata.reserve(nStrips);

    // Create array of time data
    for (uint i = 0; i < nSamples; i++)
        tdata[i] = i;

    // Create `nstrips` arrays of y data and associated plot curves
    for (uint i = 0; i < nStrips; i++) {
        lines.emplace_back(new QwtPlotCurve);
        auto &line = **lines.rbegin();
        line.setPen(lineColours[i % lineColours.size()]);
        line.attach(plot);

        QVector<double> linedata(nSamples);
        ydata.append(linedata);
        line.setSamples(tdata, linedata);
    }

    // Configure plot
    plot->axisScaleDraw(QwtPlot::xBottom)->
            enableComponent(QwtAbstractScaleDraw::Labels, false);
    plot->setAxisScale(QwtPlot::xBottom, 0, nSamples);

    q->setSpacing(spacing);
}

/*!
 * Redraw the plot if necessary. Called periodically by the timer.
 */
void StripChartPrivate::redraw()
{
    // If no data has arrived during the last refresh period, stop the timer.
    if (!needsRedraw) {
        timer->stop();
        return;
    }

    // Re-plot data
    for (uint i = 0; i < lines.size(); i++)
        lines[i]->setSamples(tdata, ydata[i]);
    plot->replot();
    needsRedraw = false;
}


/*!
 * Construct a new StripChart as a child of the given \a parent;
 */
StripChart::StripChart(QWidget *parent) :
    QWidget(parent),
    d_ptr(new StripChartPrivate(this))
{
    d_ptr->createStrips();
}

StripChart::~StripChart() { }

/*!
 * Append \a data to the StripChart. The cardinality of the given \a data must
 * be equal to \c nStrips.
 */
void StripChart::appendData(const std::vector<double> &data)
{
    Q_D(StripChart);
    Q_ASSERT(data.size() == d->nStrips);

    for (size_t i = 0; i < data.size(); i++) {
        d->ydata[i].pop_front();
        d->ydata[i].push_back(data[i] - i * d->spacing);
    }

    // Keep note that we have new data to plot
    bool first_data = !d->needsRedraw;
    d->needsRedraw = true;

    // Start the timer to redraw at the specified rate
    if (!d->timer->isActive()) {
        if (first_data) d->redraw();
        d->timer->start(1e3 / d->rate);
    }
}

/*!
 * The number of channels of data to display.
 */
uint StripChart::nStrips() const
{
    Q_D(const StripChart);
    return d->nStrips;
}

/*!
 * Set the number of channels of data to display.
 */
void StripChart::setNStrips(uint n)
{
    Q_D(StripChart);
    d->nStrips = n;
    d->createStrips();
}

/*!
 * The width of the StripChart in samples.
 */
uint StripChart::nSamples() const
{
    Q_D(const StripChart);
    return d->nSamples;
}

/*!
 * Set the width of the StripChart to \a n samples.
 */
void StripChart::setNSamples(uint n)
{
    Q_D(StripChart);
    d->nSamples = n;
    d->createStrips();
}

/*!
 * \property StripChart::stripSpacing
 * The distance between adjacent strips.
 */
double StripChart::spacing() const
{
    Q_D(const StripChart);
    return d->spacing;
}

/*!
 * \fn StripChart::setSpacing(int)
 * Set the distance between adjacent strips in y-axis units.
 */
/*!
 * Set the distance between adjacent strips in y-axis units.
 */
void StripChart::setSpacing(double spacing)
{
    Q_D(StripChart);
    double delta = spacing - d->spacing;
    d->spacing = spacing;

    if (delta) {
        for (uint i = 0; i < d->nStrips; i++) {
            for (uint t = 0; t < d->nSamples; t++) {
                d->ydata[i][t] -= i * delta;
            }
            d->lines[i]->setSamples(d->tdata, d->ydata[i]);
        }
    }

    d->plot->setAxisScaleDraw(QwtPlot::yLeft, new StripChartScaleDraw(d->spacing));
    d->plot->setAxisScale(QwtPlot::yLeft,
                          -(d->nStrips - 0.01) * d->spacing,
                          0.99 * d->spacing,
                          d->spacing);

    d->needsRedraw = true;
    d->redraw();
}

/*!
 * The number of milliseconds between plot redraws.
 */
uint StripChart::rate() const
{
    Q_D(const StripChart);
    return d->rate;
}

}} // namespace elapse::widgets
