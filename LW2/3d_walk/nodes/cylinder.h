#pragma once

#include "../gl/scenenode.h"


class Cylinder : public SceneNode
{
public:
    Cylinder(SceneNode *parent);

    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
};
