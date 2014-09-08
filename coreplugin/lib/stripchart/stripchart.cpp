#include <QTimer>
#include <QVBoxLayout>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include "stripchart.h"


static const QList<QColor> lineColours = {
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


namespace elapse { namespace widgets {

/*!
 * Construct a new StripChart as a child of the given \a parent;
 */
StripChart::StripChart(QWidget *parent) :
    QWidget(parent),
    plot(new QwtPlot(parent)),
    _nStrips(1),
    _nSamples(100),
    _spacing(1.0),
    _rate(10),
    timer(new QTimer)
{
    // Create a layout and add the plot
    layout = new QVBoxLayout;
    layout->addWidget(plot);
    setLayout(layout);

    plot->setCanvasBackground(Qt::white);

    createStrips();

    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
}

/*!
 * Destroy this StripChart.
 */
StripChart::~StripChart()
{
    delete timer;
    delete layout;
    qDeleteAll(lines);
    delete plot;
}

/*!
 * Helper function to set up the QwtPlotCurves, axis labels, and so on given the
 * current configuration.
 */
void StripChart::createStrips()
{
    // Delete any existing lines
    qDeleteAll(lines);
    lines.clear();
    ydata.clear();

    tdata.resize(_nSamples);
    ydata.reserve(_nStrips);

    // Create array of time data
    for (uint i = 0; i < _nSamples; i++)
        tdata[i] = i;

    // Create `nstrips` arrays of y data and associated plot curves
    for (uint i = 0; i < _nStrips; i++) {
        QwtPlotCurve *line = new QwtPlotCurve;
        line->setPen(lineColours[i % lineColours.size()]);
        line->attach(plot);
        lines.append(line);

        QVector<double> linedata(_nSamples);
        ydata.append(linedata);
        line->setSamples(tdata, linedata);
    }

    // Configure plot
    plot->axisScaleDraw(QwtPlot::xBottom)->
            enableComponent(QwtAbstractScaleDraw::Labels, false);
    plot->setAxisScale(QwtPlot::xBottom, 0, _nSamples);

    setSpacing(_spacing);
}

/*!
 * Append \a data to the StripChart. The cardinality of the given \a data must
 * be equal to \c nStrips.
 */
void StripChart::appendData(const std::vector<double> &data)
{
    Q_ASSERT(uint(data.size()) == _nStrips);

    for (size_t i = 0; i < data.size(); i++) {
        ydata[i].pop_front();
        ydata[i].push_back(data[i] - i * _spacing);
    }

    // Keep note that we have new data to plot
    bool first_data = !needs_redraw;
    needs_redraw = true;

    // Start the timer to redraw at the specified rate
    if (!timer->isActive()) {
        if (first_data) redraw();
        timer->start(1e3 / _rate);
    }
}

/*!
 * Redraw the plot if necessary. Called periodically by the timer.
 */
void StripChart::redraw()
{
    // If no data has arrived during the last refresh period, stop the timer.
    if (!needs_redraw) {
        timer->stop();
        return;
    }

    // Re-plot data
    for (int i = 0; i < lines.size(); i++)
        lines[i]->setSamples(tdata, ydata[i]);
    plot->replot();
    needs_redraw = false;
}

/*!
 * \property StripChart::nStrips
 * The number of channels of data to display.
 */
/*!
 * Set the number of channels of data to display.
 */
void StripChart::setNStrips(uint n)
{
    _nStrips = n;
    createStrips();
}

/*!
 * \property StripChart::nSamples
 * The width of the StripChart in samples.
 */
/*!
 * Set the width of the StripChart to \a n samples.
 */
void StripChart::setNSamples(uint n)
{
    _nSamples = n;
    createStrips();
}

/*!
 * \property StripChart::stripSpacing
 * The distance between adjacent strips.
 */
/*!
 * \fn StripChart::setSpacing(int)
 * Set the distance between adjacent strips in y-axis units.
 */
/*!
 * Set the distance between adjacent strips in y-axis units.
 */
void StripChart::setSpacing(double spacing)
{
    double delta = spacing - _spacing;
    _spacing = spacing;

    if (delta) {
        for (uint i = 0; i < _nStrips; i++) {
            for (uint t = 0; t < _nSamples; t++) {
                ydata[i][t] -= i * delta;
            }
            lines[i]->setSamples(tdata, ydata[i]);
        }
    }

    plot->setAxisScaleDraw(QwtPlot::yLeft, new StripChartScaleDraw(_spacing));
    plot->setAxisScale(QwtPlot::yLeft,
                       -(_nStrips - 0.01) * _spacing,
                       0.99 * _spacing,
                       _spacing);

    needs_redraw = true;
    redraw();
}

/*!
 * \property StripChart::rate
 * The number of milliseconds between plot redraws.
 */

}} // namespace elapse::widgets
