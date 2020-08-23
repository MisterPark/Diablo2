#pragma once
#include "GameObject.h"
class Character :
    public GameObject
{
    // GameObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;
};

