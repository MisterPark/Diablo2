#pragma once
#include "UI.h"

class Label;

class Button : public UI
{
public:
    Button();
    virtual ~Button();


    virtual void Update() override;
    virtual void Render() override;

    virtual void OnClick() override;
    virtual void OnLButtonDown() override;
    virtual void OnLButtonUp() override;
    virtual void OnHover();
    virtual void OnLeave();
    virtual void OnChangedText();

    void SetFont(const wstring& faceName, int size, UINT fontWeight);
    
    RECT labelRect = {};
    Label* pLabel = nullptr;
};

