#pragma once
#include "UI.h"
class Panel_Status :
    public UI
{
private:
    Panel_Status();
    virtual ~Panel_Status();
public:
    static Panel_Status* GetInstance();
    static void Destroy();

    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;

    virtual void OnClick();
    virtual void OnLButtonDown();
    virtual void OnLButtonUp();
    virtual void OnHover();
    virtual void OnLeave();
    virtual void OnChangedText();
};

