#pragma once
#include "IScene.h"
class IntroScene :
    public IScene
{
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    float tick = 0.f;
    float delay = 10.f;
};

