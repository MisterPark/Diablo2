#pragma once
#include "Missile.h"
class Firebolt :
    public Missile
{
public:
    Firebolt();
    virtual ~Firebolt();

    virtual void Update()override;
};

