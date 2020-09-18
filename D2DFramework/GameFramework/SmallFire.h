#pragma once
#include "Missile.h"
class SmallFire :
    public Missile
{
public:
    SmallFire();
    virtual ~SmallFire();

    virtual void Update();
    virtual void Render();
};

