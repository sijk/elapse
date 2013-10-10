#include <QTimer>
#include <QVBoxLayout>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include "stripchart.h"


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

StripChart::~StripChart()
{
    delete timer;
    delete layout;
    while (!lines.isEmpty())
        delete lines.takeFirst();
    delete plot;
}

void StripChart::createStrips()
{
    // Delete any existing lines
    while (!lines.isEmpty())
        delete lines.takeFirst();
    ydata.clear();

    tdata.resize(_nSamples);
    ydata.reserve(_nStrips);

    // Create array of time data
    for (uint i = 0; i < _nSamples; i++)
        tdata[i] = i;

    // Create `nstrips` arrays of y data and associated plot curves
    for (uint i = 0; i < _nStrips; i++) {
        QwtPlotCurve *line = new QwtPlotCurve;
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

void StripChart::appendData(const QVector<double> &data)
{
    Q_ASSERT(uint(data.size()) == _nStrips);

    for (int i = 0; i < data.size(); i++) {
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

void StripChart::setNStrips(uint n)
{
    _nStrips = n;
    createStrips();
}

void StripChart::setNSamples(uint n)
{
    _nSamples = n;
    createStrips();
}

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
