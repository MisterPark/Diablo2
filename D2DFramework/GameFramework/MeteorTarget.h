#pragma once
#include "Effect.h"
class MeteorTarget :
    public Effect
{
public:
    MeteorTarget();
    virtual ~MeteorTarget();

    virtual void Update();

    float lifeTick = 0.f;
    float lifeDuration = 4.f;
};

