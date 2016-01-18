#include "window3d.h"
#include <QResizeEvent>
#include <QPainter>
#include <QGuiApplication>
#include <QPoint>
#include <QVector3D>
#include <cmath>

Window3D::Window3D(QWindow *parent)
    : QWindow(parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    //setFlags(Qt::Window);
}

void Window3D::setFixedSize(QSize size)
{
    setMinimumSize(size);
    setMaximumSize(size);
}

void Window3D::pushScene(std::shared_ptr<BaseScene> scene)
{
    m_sceneStack.push_back(scene);
    scene->onPush();
}

void Window3D::popScene()
{
    if (!m_sceneStack.empty())
    {
        m_sceneStack.back()->onPop();
        m_sceneStack.pop_back();
    }
}

bool Window3D::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_updatePending = false;
        render();
        return true;
    case QEvent::Close:
        if (m_canRender)
        {
            stopRendering();
        }
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void Window3D::exposeEvent(QExposeEvent *event)
{
    QWindow::exposeEvent(event);
    if (isExposed())
        render();
}

void Window3D::resizeEvent(QResizeEvent *event)
{
    QWindow::resizeEvent(event);
    if (!m_canRender)
    {
        initRendering();
    }
}

void Window3D::showEvent(QShowEvent *event)
{
    QWindow::showEvent(event);
}

void Window3D::deferRender()
{
    if (!m_updatePending) {
        m_updatePending = true;
        QGuiApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void Window3D::render()
{
    if (!m_canRender)
    {
        return;
    }

    m_pContext->makeCurrent(this);
    if (!m_sceneStack.empty())
    {
        updateScene(*m_sceneStack.back());
    }
    else
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    m_pContext->swapBuffers(this);
    deferRender();
}

void Window3D::stopRendering()
{
    while (!m_sceneStack.empty())
    {
        popScene();
    }
    m_canRender = false;
}

void Window3D::initRendering()
{
    if (!m_pContext) {
        m_pContext = new QOpenGLContext(this);
        m_pContext->setFormat(requestedFormat());
        m_pContext->create();
    }
    m_canRender = true;
    m_updateTime.start();
}

void Window3D::updateScene(BaseScene &scene)
{
    scene.setViewport(size());

    int msec = m_updateTime.elapsed();
    m_updateTime.restart();
    scene.visit([&](SceneNode & node) {
        node.advance(msec);
    });
    scene.camera().advance(msec);

    QOpenGLPaintDevice device(size());
    QPainter painter(&device);
    scene.camera().loadMatrix();
    scene.render(painter);
    scene.visit([&](SceneNode & node) {
        node.render(painter);
    });
}

// rotatingCamera events
/*
void Window3D::mousePressEvent(QMouseEvent *ev)
{
    m_prevMouseX = ev->x();
    m_prevMouseY = ev->y();
}

void Window3D::mouseMoveEvent(QMouseEvent *ev)
{
    qreal sensivity = 0.03;

    if (ev->buttons() & Qt::LeftButton)
    {
        int curX = ev->x();
        int curY = ev->y();
        int dx = curX - m_prevMouseX;
        int dy = curY - m_prevMouseY;
        m_prevMouseX = curX;
        m_prevMouseY = curY;

        auto scene = m_sceneStack.back().get();

        scene->camera().rotateZ(dx*sensivity);
        scene->camera().rotateViewAngle(-dy*sensivity);

        render();
    }
}

void Window3D::wheelEvent(QWheelEvent *ev)
{
    qreal sensivity = -0.005;
    int dr = ev->angleDelta().y();

    auto scene = m_sceneStack.back().get();
    scene->camera().modifyRadius(dr*sensivity);

    render();
}
*/


// FreeCamera events

void Window3D::mousePressEvent(QMouseEvent *ev)
{
    m_sceneStack.back().get()->camera().onMouseDown(ev);
}

void Window3D::wheelEvent(QWheelEvent *ev)
{
    m_sceneStack.back().get()->camera().onWheelMove(ev);
}

void Window3D::mouseMoveEvent(QMouseEvent *ev)
{
    m_sceneStack.back().get()->camera().onMouseMove(ev);
}

void Window3D::keyPressEvent(QKeyEvent *ev)
{    
    auto scene = m_sceneStack.back().get();
    scene->camera().onKeyDown(ev);

    if (ev->key() == Qt::Key_Tab)
    {
        scene->switchCameras();
    }
}

void Window3D::keyReleaseEvent(QKeyEvent *ev)
{
    m_sceneStack.back().get()->camera().onKeyUp(ev);
}
