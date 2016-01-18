#pragma once

#include <QVector3D>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

class ISceneCamera
{
public:
    virtual void loadMatrix() const = 0;
    virtual void lookAt(QVector3D const& eye,
                        QVector3D const& at,
                        QVector3D const& up) = 0;
    virtual void advance(int64_t msec) = 0;

    virtual void setViewport(QSize size) = 0;
    virtual QSize viewport() const = 0;
    virtual QVector3D eye() const = 0;

    virtual void onKeyDown(QKeyEvent *) = 0;
    virtual void onKeyUp(QKeyEvent *) = 0;
    virtual void onMouseDown(QMouseEvent *) = 0;
    virtual void onMouseMove(QMouseEvent *) = 0;
    virtual void onWheelMove(QWheelEvent *) = 0;
};
