#pragma once
#include "Missile.h"
class Meteor :
    public Missile
{
public:
    Meteor();
    virtual ~Meteor();

    virtual void Update();
    virtual void Render();

    void SetMeteorTarget(Vector3 _pos);

private:
    Vector3 targetPos;
    
};

