#pragma once
#include "UI.h"
class Label : public UI
{
public:
    Label();
    virtual ~Label();


    virtual void Update() override;
    virtual void Render() override;

    virtual void OnClick() override;
    virtual void OnLButtonDown() override;
    virtual void OnLButtonUp() override;
    virtual void OnHover();
    virtual void OnLeave();
    virtual void OnChangedText();

    virtual int Width();
    virtual int Height();

    void SetFont(const wstring& faceName, int size, UINT weight);
    void SetColor(D3DXCOLOR color);
    void SetRect(bool _isDrawRect);

    LPD3DXFONT pFont = nullptr;
    INT size = 0;
    UINT fontWeight = 0;
    D3DXCOLOR color = D3DCOLOR_ARGB(255, 0, 0, 0);
    RECT textArea = {};
    bool isDrawRect = false;
};

