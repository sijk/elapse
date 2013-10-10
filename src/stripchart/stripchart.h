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
    Q_PROPERTY(uint nStrips MEMBER _nStrips WRITE setNStrips)
    Q_PROPERTY(uint nSamples MEMBER _nSamples WRITE setNSamples)
    Q_PROPERTY(double stripSpacing MEMBER _spacing WRITE setSpacing)
    Q_PROPERTY(uint rate MEMBER _rate)

public:
    explicit StripChart(QWidget *parent = nullptr);
    ~StripChart();

public slots:
    void appendData(const QVector<double> &data);

    void setNStrips(uint n);
    void setNSamples(uint n);
    void setSpacing(double spacing);
    void setSpacing(int spacing) { setSpacing(double(spacing)); }

private slots:
    void redraw();

private:
    void createStrips();

    QVBoxLayout *layout;
    QwtPlot *plot;
    QList<QwtPlotCurve*> lines;
    QVector<double> tdata;
    QList<QVector<double>> ydata;

    uint _nStrips;
    uint _nSamples;
    double _spacing;
    uint _rate;

    QTimer *timer;
    bool needs_redraw;
};

#endif // STRIPCHART_H
