#pragma once

#include <QObject>
#include <QVector3D>
#include <QSize>
#include <stdint.h>
#include "iscenecamera.h"

/// Static camera, can be manually controlled.
class RotatingCamera : public QObject, public ISceneCamera
{
    Q_OBJECT
    Q_DISABLE_COPY(RotatingCamera)
    Q_PROPERTY(QSize viewport READ viewport WRITE setViewport)
    Q_PROPERTY(QVector3D eye READ eye)
public:
    explicit RotatingCamera(QSize viewport, QObject *parent = 0);

    void loadMatrix() const override;
    void lookAt(QVector3D const &eye, QVector3D const& at, QVector3D const& up) override;
    /// @param msec - milliseconds since last advance or creation.
    void advance(int64_t msec) override;

    QSize viewport() const override;
    void setViewport(QSize viewport) override;
    QVector3D eye() const override;

    void onKeyDown(QKeyEvent *ev) override;
    void onKeyUp(QKeyEvent *ev) override;
    void onMouseDown(QMouseEvent *ev) override;
    void onMouseMove(QMouseEvent *ev) override;
    void onWheelMove(QWheelEvent *ev) override;

private:
    void rotateZ(qreal dl);
    void rotateViewAngle(qreal dl);
    void modifyRadius(qreal dr);

private:
    QSize m_viewport;
    QVector3D m_eye;   /**< Eye position */
    QVector3D m_front; /**< Front direction */
    QVector3D m_up;    /**< Up direction */
    QVector3D m_speed; /**< Speed, meters per second, front/left/up */

    qreal m_radius;
    QVector3D m_at;

    int m_prevMouseX;
    int m_prevMouseY;
};
