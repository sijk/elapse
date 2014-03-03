#include <math.h>
#include <QtWidgets>
#include <QtOpenGL>
#include "headmesh.h"
#include "headwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

HeadWidget::HeadWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    head = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;

    headColour = QColor::fromCmykF(0.0, 0.1, 0.2, 0.3);
    bgndColour = QColor::fromRgb(30, 30, 60);
}

HeadWidget::~HeadWidget()
{
}

QSize HeadWidget::minimumSizeHint() const
{
    return QSize(40, 50);
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
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void HeadWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void HeadWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
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
    qglClearColor(bgndColour);

    head = new HeadMesh(this);
    head->setColor(headColour);

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
    // Centre of rotation
    float x0 = 0, y0 = -0.3, z0 = -0.2;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glTranslatef(x0, y0, z0);
    // Intrinsic rotation about (x0,y0,z0)
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glTranslatef(-x0, -y0, -z0);
    head->draw();
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

void HeadWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void HeadWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
