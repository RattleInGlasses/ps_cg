#include "freecamera.h"
#include "glhelper.h"
#include <QMatrix4x4>
#include <QGenericMatrix>
#include <cmath>

const qreal CAMERA_MOVE_SPEED = 3;
const qreal CAMERA_ROTATION_SPEED = 0.3;

namespace
{
    QVector3D RotateVector(QVector3D const &vec3D, QVector3D const &axis, qreal angle)
    {
        QMatrix4x4 transformationMatrix;
        transformationMatrix.rotate(angle, axis);
        QVector4D vec4D(vec3D);
        vec4D = vec4D * transformationMatrix;
        return vec4D.toVector3D();
    }

    QVector3D MoveVector(QVector3D const &vector, QVector3D const &axis, qreal distance)
    {
        return QVector3D(vector + axis * (distance / axis.length()));
    }
}


FreeCamera::FreeCamera(QSize viewport, QObject *parent)
    : QObject(parent)
    , m_viewport(viewport)
{
}

void FreeCamera::loadMatrix() const
{
    QMatrix4x4 matrix;
    matrix.lookAt(m_eye, m_eye + m_front, m_up);
    GLHelper::setModelViewMatrix(matrix);
}

void FreeCamera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    m_eye = eye;
    m_front = at - eye;
    m_up = up;
    m_front.normalize();
}

void FreeCamera::advance(int64_t msec)
{
    QVector3D left = QVector3D::crossProduct(m_up, m_front);
    float seconds = float(msec) * 0.001f;

    m_eye = (m_movingRight) ? MoveVector(m_eye, left, -CAMERA_MOVE_SPEED * seconds) : m_eye;
    m_eye = (m_movingLeft) ? MoveVector(m_eye, left, CAMERA_MOVE_SPEED * seconds) : m_eye;
    m_eye = (m_movingForward) ? MoveVector(m_eye, m_front, CAMERA_MOVE_SPEED * seconds) : m_eye;
    m_eye = (m_movingBackwards) ? MoveVector(m_eye, m_front, -CAMERA_MOVE_SPEED * seconds) : m_eye;
}

QSize FreeCamera::viewport() const
{
    return m_viewport;
}

void FreeCamera::setViewport(QSize viewport)
{
    m_viewport = viewport;
}

QVector3D FreeCamera::eye() const
{
    return m_eye;
}

void FreeCamera::onKeyDown(QKeyEvent *ev)
{
    switch (ev->key())
    {
    case Qt::Key_Left:
        m_movingLeft = true;
        break;
    case Qt::Key_Right:
        m_movingRight = true;
        break;
    case Qt::Key_Up:
        m_movingForward = true;
        break;
    case Qt::Key_Down:
        m_movingBackwards = true;
        break;
    }
}

void FreeCamera::onKeyUp(QKeyEvent *ev)
{
    switch (ev->key())
    {
    case Qt::Key_Left:
        m_movingLeft = false;
        break;
    case Qt::Key_Right:
        m_movingRight = false;
        break;
    case Qt::Key_Up:
        m_movingForward = false;
        break;
    case Qt::Key_Down:
        m_movingBackwards = false;
        break;
    }
}

void FreeCamera::onMouseDown(QMouseEvent *ev)
{
    m_prevMouseX = ev->x();
    m_prevMouseY = ev->y();
}

void FreeCamera::onMouseMove(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
        int curX = ev->x();
        int curY = ev->y();
        int dx = curX - m_prevMouseX;
        int dy = curY - m_prevMouseY;
        m_prevMouseX = curX;
        m_prevMouseY = curY;

        rotateUp(-dy * CAMERA_ROTATION_SPEED);
        rotateRight(dx * CAMERA_ROTATION_SPEED);
    }
}

void FreeCamera::onWheelMove(QWheelEvent *)
{
}

void FreeCamera::rotateRight(qreal angle)
{
    m_front = RotateVector(m_front, m_up, angle);
    m_front.normalize();
}

void FreeCamera::rotateUp(qreal angle)
{
    QVector3D axis = QVector3D::crossProduct(m_up, m_front);
    m_front = RotateVector(m_front, axis, angle);
    m_up = RotateVector(m_up, axis, angle);
    m_front.normalize();
    m_up.normalize();
}

void FreeCamera::initMousePosition(QMouseEvent *ev)
{
    m_prevMouseX = ev->x();
    m_prevMouseY = ev->y();
}

