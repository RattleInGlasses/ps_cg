#pragma once

#include <QObject>
#include "iscenecamera.h"

class FreeCamera : public QObject, public ISceneCamera
{
    Q_OBJECT
    Q_DISABLE_COPY(FreeCamera)
    Q_PROPERTY(QSize viewport READ viewport WRITE setViewport)
    Q_PROPERTY(QVector3D eye READ eye)
public:
    explicit FreeCamera(QSize viewport, QObject *parent = 0);

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
    void rotateRight(qreal angle);
    void rotateUp(qreal angle);
    void initMousePosition(QMouseEvent *ev);

private:
    QSize m_viewport;
    QVector3D m_eye;   /**< Eye position */
    QVector3D m_front; /**< Front direction */
    QVector3D m_up;    /**< Up direction */

    int m_prevMouseX;
    int m_prevMouseY;

    bool m_movingRight = false;
    bool m_movingLeft = false;
    bool m_movingForward = false;
    bool m_movingBackwards = false;
};

