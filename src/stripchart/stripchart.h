#ifndef STRIPCHART_H
#define STRIPCHART_H

#include <QWidget>

class QVBoxLayout;
class QTimer;
class QwtPlot;
class QwtPlotCurve;

class StripChart : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(uint rate MEMBER _rate)
    Q_PROPERTY(double stripSpacing MEMBER _space)

public:
    explicit StripChart(QWidget *parent = nullptr);
    ~StripChart();

public slots:
    void appendData(const QVector<double> &data);

private slots:
    void redraw();

private:
    QVBoxLayout *layout;
    QwtPlot *plot;
    QList<QwtPlotCurve*> lines;
    QVector<double> tdata;
    QList<QVector<double>> ydata;
    double _space;

    QTimer *timer;
    uint _rate;
    bool needs_redraw;
};

#endif // STRIPCHART_H
