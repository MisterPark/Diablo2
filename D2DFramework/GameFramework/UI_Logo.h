#pragma once
#include "UI.h"
class UI_Logo :
    public UI
{
public:
    UI_Logo();
    virtual ~UI_Logo();

    virtual void Update()override;
    virtual void Render()override;
};

