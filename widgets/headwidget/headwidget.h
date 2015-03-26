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
