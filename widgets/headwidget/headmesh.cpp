#include <QGLWidget>
#include "headmesh.h"
#include "obj/head.h"


void HeadMesh::setColor(QColor c)
{
    color[0] = c.redF();
    color[1] = c.greenF();
    color[2] = c.blueF();
    color[3] = c.alphaF();
}

void HeadMesh::draw() const
{
    glVertexPointer(3, GL_FLOAT, 0, headVerts);
    glNormalPointer(GL_FLOAT, 0, headNormals);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glDrawArrays(GL_TRIANGLES, 0, headNumVerts);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
