#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QGLWidget>
#include <QScopedPointer>

namespace elapse { namespace widgets {

class HeadWidgetPrivate;

/*!
 * \brief The HeadWidget class displays a 3D head in a configurable orientation.
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
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setXRotation(double radians);
    void setYRotation(double radians);
    void setZRotation(double radians);

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
