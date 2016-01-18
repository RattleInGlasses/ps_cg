#pragma once

#include <QObject>
#include <QSize>
#include <QVector3D>
#include "rotatingcamera.h"
#include "freecamera.h"
#include "iscenecamera.h"


class ViewContorller : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ViewContorller)

public:
    ViewContorller(QSize viewportSize, QObject *parent = 0);
    void setViewport(QSize viewport);

    ISceneCamera& camera();
    const ISceneCamera& camera() const;

    void switchCameras();

private:
    FreeCamera m_freeCamera;
    RotatingCamera m_rotatingCamera;
    ISceneCamera* m_camera;
};

