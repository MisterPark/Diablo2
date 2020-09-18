#pragma once
#include "Missile.h"
class FireWall :
    public Missile
{
public:
    FireWall();
    virtual ~FireWall();

    virtual void Update();
    virtual void Render();
};

