#include <qopengl.h>
#include <QVector>
#include "cylinder.h"

struct Vec3
{
    GLfloat x, y, z;
};

namespace
{
    QVector<Vec3> getCircle(GLfloat r, Vec3 const& center, uint precision)
    {
        (void)r;
        (void)center;
        (void)precision;
        return {
            center,
            { 1,  0,  1},
            {-1,  0,  1},
            {-1,  0, -1},
            { 1,  0, -1}
        };
    }

    void drawCircle(QVector<Vec3> const& circle)
    {
        //glEnableClientState(GL_VERTEX_ARRAY);

       // glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);

        //glDrawElements(GL_TRIANGLE_FAN, 3, GL_UNSIGNED_BYTE, faces);

        //glDisableClientState(GL_VERTEX_ARRAY);

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0,1.0,0.0);

        const unsigned char faces[1][3] =
        {
            {0, 2, 1}//,
            //{0, 1, 4},
            //{0, 3, 4},
            //{0, 3, 2},
        };

        //glVertexPointer(3, GL_FLOAT, 0, &circle[0]);
        //glEnableClientState(GL_VERTEX_ARRAY);
        //glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_BYTE, faces);
        //glDisableClientState(GL_VERTEX_ARRAY);

        GLfloat pVerts[]= {-0.5f, -0.5f, 0.0f,

                            0.5f,  0.0f, 0.0f,

                           -0.5f , 0.5f, 0.0f,
                           -0.5f,  0.0f, 0.0f};
        //glEnableClientState(GL_VERTEX_ARRAY);
        //glVertexPointer(3, GL_FLOAT, 0, pVerts);
        //glDrawArrays(GL_TRIANGLE_FAN,0,4);

        //glDisableClientState(GL_VERTEX_ARRAY);

        glBegin(GL_TRIANGLE_FAN);
            glVertex3f( 0,  0, 0);
            glVertex3f( 1,  1, 0);
            glVertex3f(-1,  1, 0);
            glVertex3f(-1, -1, 0);
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
         glColor3d(0,0,1);
         glVertex3d(4,2,0);
         glVertex3d(2.6,2.8,0);
         glVertex3d(2,2,0);
         glVertex3d(3,1.1,0);
        glEnd();
    }
}


Cylinder::Cylinder(SceneNode *parent)
    : SceneNode(parent)
{
}

void Cylinder::advance(int64_t msec)
{
    (void)msec;
}

void Cylinder::render(QPainter &painter)
{
    (void)painter;

    GLfloat r = 100;
    GLfloat h = 100;
    uint precision = 4;

    Vec3 bottomCircleCenter = { 0, 0, 0 };
    Vec3 topCircleCenter = { 0, bottomCircleCenter.y + h, 0 };

    QVector<Vec3> topCircle = getCircle(r, topCircleCenter, precision);
    //QVector<Vec3> bottomCircle = getCircle;

    drawCircle(topCircle);
}



