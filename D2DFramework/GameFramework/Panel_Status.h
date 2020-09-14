#pragma once
#include "UI.h"

class Label;

class Panel_Status :
    public UI
{
private:
    Panel_Status();
    virtual ~Panel_Status();
public:
    static Panel_Status* GetInstance();
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


    
    Label* nick                   =nullptr;
    Label* className              =nullptr;
    Label* labels[MaxOfEnum<StatType>()] = {};
};

