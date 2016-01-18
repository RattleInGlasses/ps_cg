#include "viewcontorller.h"


ViewContorller::ViewContorller(QSize viewportSize, QObject *parent)
    : QObject(parent)
    , m_rotatingCamera(viewportSize)
    , m_freeCamera(viewportSize)
{
    m_camera = &m_rotatingCamera;
}

void ViewContorller::setViewport(QSize viewport)
{
    m_rotatingCamera.setViewport(viewport);
    m_freeCamera.setViewport(viewport);
}

ISceneCamera& ViewContorller::camera()
{
    return *m_camera;
}

const ISceneCamera& ViewContorller::camera() const
{
    return *m_camera;
}

void ViewContorller::switchCameras()
{
    //m_camera = (m_camera == &m_rotatingCamera) ? &m_freeCamera : &m_rotatingCamera;
    if (m_camera == &m_rotatingCamera)
    {
        m_camera = &m_freeCamera;
    }
    else
    {
        m_camera = &m_rotatingCamera;
    }
}
