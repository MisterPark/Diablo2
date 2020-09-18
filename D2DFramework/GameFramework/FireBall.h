#pragma once
#include "Missile.h"
class FireBall :
    public Missile
{
public:
    FireBall();
    virtual ~FireBall();

    virtual void Update() override;
};

