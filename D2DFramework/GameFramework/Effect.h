#pragma once
#include "GameObject.h"
class Effect :
    public GameObject
{
public:
    Effect();
    virtual ~Effect();
    // GameObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;
};

