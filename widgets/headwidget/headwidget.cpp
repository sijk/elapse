#include <math.h>
#include <QtWidgets>
#include <QtOpenGL>
#include "headmesh.h"
#include "headwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

static const QColor headColour = QColor::fromCmykF(0.0, 0.1, 0.2, 0.3);
static const QColor bgndColour = QColor::fromRgb(30, 30, 60);

namespace elapse { namespace widgets {

class HeadWidgetPrivate
{
public:
    QScopedPointer<HeadMesh> head;
    int xRot = 0;
    int yRot = 0;
    int zRot = 0;
    RateLimiter update {30};
};

HeadWidget::HeadWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

HeadWidget::~HeadWidget()
{
}

QSize HeadWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize HeadWidget::sizeHint() const
{
    return QSize(200, 250);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void HeadWidget::setXRotation(int angle)
{
    Q_D(HeadWidget);
    qNormalizeAngle(angle);
    if (angle != d->xRot) {
        d->xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void HeadWidget::setYRotation(int angle)
{
    Q_D(HeadWidget);
    qNormalizeAngle(angle);
    if (angle != d->yRot) {
        d->yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void HeadWidget::setZRotation(int angle)
{
    Q_D(HeadWidget);
    qNormalizeAngle(angle);
    if (angle != d->zRot) {
        d->zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void HeadWidget::setXRotation(double radians)
{
    setXRotation(int(radians * 180 / M_PI * 16));
}

void HeadWidget::setYRotation(double radians)
{
    setYRotation(int(radians * 180 / M_PI * 16));
}

void HeadWidget::setZRotation(double radians)
{
    setZRotation(int(radians * 180 / M_PI * 16));
}

void HeadWidget::initializeGL()
{
    Q_D(HeadWidget);
    qglClearColor(bgndColour);

    d->head.reset(new HeadMesh(this));
    d->head->setColor(headColour);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void HeadWidget::paintGL()
{
    Q_D(HeadWidget);
    // Centre of rotation
    float x0 = 0, y0 = -0.3, z0 = -0.2;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glTranslatef(x0, y0, z0);
    // Intrinsic rotation about (x0,y0,z0)
    glRotatef(d->zRot / 16.0, 0.0, 0.0, 1.0);
    glRotatef(d->yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(d->xRot / 16.0, 1.0, 0.0, 0.0);
    glTranslatef(-x0, -y0, -z0);
    d->head->draw();
}

void HeadWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

}} // namespace elapse::widgets
