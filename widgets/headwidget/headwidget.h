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

#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QGLWidget>
#include <QScopedPointer>

namespace elapse { namespace widgets {

class HeadWidgetPrivate;

/*!
 * \brief The HeadWidget class displays a 3D head in a configurable orientation.
 *
 * The widget uses intrinsic rotations measured in radians. That is, the
 * rotations are taken about axes that are fixed to the head, not about the
 * world's axes. The x axis points out the right ear, the y axis out the nose,
 * and the z axis out the top of the head.
 *
 * \headerfile elapse/widgets/headwidget.h
 * \ingroup widgets
 */

class HeadWidget : public QGLWidget
{
    Q_OBJECT

public:
    HeadWidget(QWidget *parent = 0);
    ~HeadWidget();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setXRotation(float radians);
    void setYRotation(float radians);
    void setZRotation(float radians);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    const QScopedPointer<HeadWidgetPrivate> d_ptr;
    Q_DECLARE_PRIVATE(HeadWidget)
};

}} // namespace elapse::widgets

#endif
