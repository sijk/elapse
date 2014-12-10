#include <QPainter>
#include "cvmatwidget.h"

namespace elapse { namespace widgets {

void CvMatWidget::showImage(const cv::Mat& image, int convert)
{
    // Convert to RGB (OpenCV uses BGR by default)
    cv::cvtColor(image, img, convert);
    // Create a shallow QImage wrapper for the cv::Mat data
    qimg = QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    if (size() != qimg.size())
        setFixedSize(qimg.size());
    update();
}

void CvMatWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QRect({0,0}, size()), qimg, QRect({0,0}, qimg.size()));
}

}} // namespace elapse::widgets
