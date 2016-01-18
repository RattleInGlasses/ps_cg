#include "rotatingcamera.h"
#include "glhelper.h"
#include <QMatrix4x4>
#include <cmath>

#define M_PI		3.14159265358979323846

const qreal CAMERA_ROTATION_SENSIVITY = 0.03;
const qreal CAMERA_ZOOM_SENSIVITY = 0.005;


RotatingCamera::RotatingCamera(QSize viewport, QObject *parent)
    : QObject(parent)
    , m_viewport(viewport)
{
}

void RotatingCamera::loadMatrix() const
{
    QMatrix4x4 matrix;
    matrix.lookAt(m_eye, m_eye + m_front, m_up);
    GLHelper::setModelViewMatrix(matrix);
}

void RotatingCamera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    m_eye = eye;
    m_front = at - eye;
    m_up = up;
    m_front.normalize();

    m_at = at;
    m_radius = sqrt(m_eye.x()*m_eye.x() + m_eye.y()*m_eye.y() + m_eye.z()*m_eye.z());
}

void RotatingCamera::advance(int64_t msec)
{
    QVector3D left = QVector3D::crossProduct(m_up, m_front);
    float seconds = float(msec) * 0.001f;
    float dFront = m_speed.x() * seconds;
    float dLeft = m_speed.y() * seconds;
    float dUp = m_speed.z() * seconds;
    m_eye += m_front * dFront;
    m_eye += left * dLeft;
    m_eye += m_up * dUp;
}

QSize RotatingCamera::viewport() const
{
    return m_viewport;
}

void RotatingCamera::setViewport(QSize viewport)
{
    m_viewport = viewport;
}

QVector3D RotatingCamera::eye() const
{
    return m_eye;
}

void RotatingCamera::rotateZ(qreal dl)
{
    qreal a = dl / sqrt(m_eye.x()*m_eye.x() + m_eye.y()*m_eye.y());
    qreal newEyePointX, newEyePointY;

    newEyePointX = cos(a)*m_eye.x() - sin(a)*m_eye.y();
    newEyePointY = sin(a)*m_eye.x() + cos(a)*m_eye.y();

    m_eye.setX(newEyePointX);
    m_eye.setY(newEyePointY);

    lookAt(m_eye, m_at, m_up);
}

void RotatingCamera::rotateViewAngle(qreal dl)
{
    qreal a = dl / m_radius;
    qreal currentAngle = asin(m_eye.z() / m_radius);
    a = (a + currentAngle > M_PI/2) ? M_PI/2 - currentAngle : (a + currentAngle < 0) ? 0 - currentAngle : a;

    qreal r1 = sqrt(m_eye.x()*m_eye.x() + m_eye.y()*m_eye.y());
    qreal newEyePointZ = sin(a)*r1 + cos(a)*m_eye.z();
    qreal r2 = cos(a)*r1 - sin(a)*m_eye.z();
    qreal newEyePointX = r2 * m_eye.x() / r1;
    qreal newEyePointY = r2 * m_eye.y() / r1;

    m_eye.setX(newEyePointX);
    m_eye.setY(newEyePointY);
    m_eye.setZ(newEyePointZ);

    lookAt(m_eye, m_at, m_up);
}

void RotatingCamera::modifyRadius(qreal dr)
{
    qreal newRadius = m_radius + dr;
    newRadius = (newRadius > 16) ? 16 : (newRadius < 3) ? 3 : newRadius;

    qreal newEyePointX, newEyePointY, newEyePointZ;
    newEyePointX = m_eye.x() * newRadius/m_radius;
    newEyePointY = m_eye.y() * newRadius/m_radius;
    newEyePointZ = m_eye.z() * newRadius/m_radius;

    m_radius = newRadius;

    m_eye.setX(newEyePointX);
    m_eye.setY(newEyePointY);
    m_eye.setZ(newEyePointZ);

    lookAt(m_eye, m_at, m_up);
}

void RotatingCamera::onKeyDown(QKeyEvent *)
{
}

void RotatingCamera::onKeyUp(QKeyEvent *)
{
}

void RotatingCamera::onMouseDown(QMouseEvent *ev)
{
    m_prevMouseX = ev->x();
    m_prevMouseY = ev->y();
}

void RotatingCamera::onMouseMove(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
        int curX = ev->x();
        int curY = ev->y();
        int dx = curX - m_prevMouseX;
        int dy = curY - m_prevMouseY;
        m_prevMouseX = curX;
        m_prevMouseY = curY;

        rotateZ(dx * CAMERA_ROTATION_SENSIVITY);
        rotateViewAngle(-dy * CAMERA_ROTATION_SENSIVITY);
    }
}

void RotatingCamera::onWheelMove(QWheelEvent *ev)
{
    int dr = ev->angleDelta().y();
    modifyRadius(-dr * CAMERA_ZOOM_SENSIVITY);
}
