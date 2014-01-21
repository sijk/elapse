#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QGLWidget>

class HeadMesh;

class HeadWidget : public QGLWidget
{
    Q_OBJECT

public:
    HeadWidget(QWidget *parent = 0);
    ~HeadWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    HeadMesh *head;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor headColour;
    QColor bgndColour;
};

#endif
