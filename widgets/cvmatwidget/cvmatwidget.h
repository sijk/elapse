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

#ifndef CVMATWIDGET_H
#define CVMATWIDGET_H

#include <QWidget>
#include <QImage>
#include <opencv2/opencv.hpp>

namespace elapse { namespace widgets {

/*!
 * \brief The CvMatWidget class is a QWidget for displaying a cv::Mat.
 * \headerfile elapse/widgets/cvmatwidget.h
 * \ingroup widgets
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
