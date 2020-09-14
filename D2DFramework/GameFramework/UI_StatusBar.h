#pragma once
#include "UI.h"

class UI_StatusBar : public UI
{
private:
    UI_StatusBar();
    virtual ~UI_StatusBar();
public:
    static UI_StatusBar* GetInstance();
    static void Destroy();

    virtual void Update();
    virtual void Render();

    virtual void OnClick();
    virtual void OnLButtonDown();
    virtual void OnLButtonUp();
    virtual void OnHover();
    virtual void OnLeave();
    virtual void OnChangedText();

    static void SetHPPercent(int max, int hp);
    static void SetMPPercent(int max, int mp);

    float perHP = 1.f;
    float perMP = 1.f;
};

