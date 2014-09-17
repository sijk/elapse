#ifndef STRIPCHART_H
#define STRIPCHART_H

#include <QWidget>
#include <memory>

class QVBoxLayout;
class QTimer;
class QwtPlot;
class QwtPlotCurve;

namespace elapse { namespace widgets {

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
 * \ingroup widgets
 */

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
    void appendData(const std::vector<double> &data);

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
    std::vector<std::unique_ptr<QwtPlotCurve>> lines;
    QVector<double> tdata;
    QList<QVector<double>> ydata;

    uint _nStrips;
    uint _nSamples;
    double _spacing;
    uint _rate;

    QTimer *timer;
    bool needs_redraw;
};

}} // namespace elapse::widgets

#endif // STRIPCHART_H
