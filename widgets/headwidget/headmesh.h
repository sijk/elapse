#ifndef HEADMESH_H
#define HEADMESH_H

#include <QObject>
#include <QColor>

/*! \private */

class HeadMesh : public QObject
{
public:
    explicit HeadMesh(QObject *parent);

    void setColor(QColor c);
    void draw() const;

private:
    float color[4];
};

#endif // HEADMESH_H
