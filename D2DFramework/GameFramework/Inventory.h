#pragma once
#include "UI.h"
class Inventory :
    public UI
{
private:
    Inventory();
    virtual ~Inventory();
public:
    static Inventory* GetInstance();
    static void Destroy();

    // GameObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;

    virtual void OnClick();
    virtual void OnLButtonDown();
    virtual void OnLButtonUp();
    virtual void OnHover();
    virtual void OnLeave();
    virtual void OnChangedText();
};

