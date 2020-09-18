#pragma once
#include "Missile.h"
class Inferno :
    public Missile
{
public:
    Inferno();
    virtual ~Inferno();

    virtual void Update();
    virtual void Render();

    float upMax = 10.f;
    float upCount = 0.000001f;
};

