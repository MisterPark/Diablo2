#pragma once
#include "UI.h"

class UI_StatusBar : public UI
{
private:
    UI_StatusBar();
    virtual ~UI_StatusBar();
public:
    static UI_StatusBar* GetInstance();
    static void DestroyInstance();

    virtual void Update();
    virtual void Render();

    virtual void OnClick();
    virtual void OnLButtonDown();
    virtual void OnLButtonUp();
    virtual void OnHover();
    virtual void OnLeave();
    virtual void OnChangedText();

    float perHP = 1.f;
    float perMP = 1.f;
    int hpX = 50;
    int hpY = 530;
};

