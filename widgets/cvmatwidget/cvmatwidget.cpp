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
