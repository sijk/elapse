#ifndef CVMATWIDGET_H
#define CVMATWIDGET_H

#include <QWidget>
#include <QImage>
#include <opencv2/opencv.hpp>

namespace elapse { namespace widgets {

/*!
 * \brief The CvMatWidget class is a QWidget for displaying a cv::Mat.
 */
class CvMatWidget : public QWidget
{
    Q_OBJECT
public:
    using QWidget::QWidget;

    /*!
     * Display the given OpenCV \a image.
     *
     * Pass the appropriate parameter to \a convert the image to RGB,
     * e.g., CV_GRAY2RGB.
     */
    void showImage(const cv::Mat &image, int convert = CV_BGR2RGB);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    cv::Mat img;
    QImage qimg;
};

}} // namespace elapse::widgets

#endif // CVMATWIDGET_H
