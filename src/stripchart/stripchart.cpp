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
    _space(6e3),
    timer(new QTimer),
    _rate(10)
{
    // FIXME
    int nstrips = 8;
    int nsamples = 1000;

    tdata.resize(nsamples);
    ydata.reserve(nstrips);

    // Create array of time data
    for (int i = 0; i < nsamples; i++)
        tdata[i] = i;

    // Create `nstrips` arrays of y data and associated plot curves
    for (int i = 0; i < nstrips; i++) {
        QwtPlotCurve *line = new QwtPlotCurve;
        line->attach(plot);
        lines.append(line);

        QVector<double> linedata(nsamples, -i*_space);
        ydata.append(linedata);
        line->setSamples(tdata, linedata);
    }

    // Configure plot
    plot->setAxisScaleDraw(QwtPlot::yLeft, new StripChartScaleDraw(_space));
    plot->setAxisScale(QwtPlot::yLeft,
                       -nstrips * _space + _space*0.01,
                       _space - _space * 0.01,
                       _space);
    plot->axisScaleDraw(QwtPlot::xBottom)->
            enableComponent(QwtAbstractScaleDraw::Labels, false);
    plot->setAxisScale(QwtPlot::xBottom, 0, nsamples, 250);

    plot->setCanvasBackground(Qt::white);

    // Create a layout and add the plot
    layout = new QVBoxLayout;
    layout->addWidget(plot);
    setLayout(layout);

    connect(timer, SIGNAL(timeout()), this, SLOT(redraw()));
}

StripChart::~StripChart()
{
    delete timer;
    delete layout;
    foreach (QwtPlotCurve *line, lines)
        delete line;
    delete plot;
}

void StripChart::appendData(const QVector<double> &data)
{
    Q_ASSERT(data.size() == ydata.size());

    for (int i = 0; i < data.size(); i++) {
        ydata[i].pop_front();
        ydata[i].push_back(data[i] - i * _space);
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
