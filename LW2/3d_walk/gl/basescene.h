#pragma once

#include "scenenode.h"
#include "rotatingcamera.h"
#include "freecamera.h"
#include "viewcontorller.h"
#include "iscenecamera.h"
#include <QColor>

class BaseScene : public SceneNode
{
    Q_OBJECT
    Q_DISABLE_COPY(BaseScene)
public:
    BaseScene(QSize viewportSize = QSize(0, 0));
    ~BaseScene();

    QColor clearColor();
    void setClearColor(const QColor &clearColor);

    void setViewport(QSize viewport);
    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
    void onPush();
    void onPop();

    void switchCameras();

    ISceneCamera &camera();
    ISceneCamera const& camera() const;

private:
    ViewContorller m_viewController;
    QColor m_clearColor;
};
