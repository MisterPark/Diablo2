#pragma once
#include "GameObject.h"
class UI : public GameObject
{
public:
    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;


    void UpdateUI();

    int X();
    int Y();
    virtual int Width();
    virtual int Height();
    void SetSpriteImage(SpriteType _type);
    void SetText(const wstring& _text);

    // �̺�Ʈ ����
    void ClearEvent();
    void UpdateEvent();
    virtual void OnClick();
    virtual void OnLButtonDown();
    virtual void OnLButtonUp();
    virtual void OnHover();
    virtual void OnLeave();
    virtual void OnChangedText();

public:

    RECT area = {};
    SpriteType sprite = SpriteType::NONE;
    int spriteIndex = 0;
    int drawIndex = 0;
    WCHAR text[64] = {};

    void (*Click)() = nullptr;
    void (*LButtonDown)() = nullptr;
    void (*LButtonUp)() = nullptr;
    void (*Hover)() = nullptr;
    void (*Leave)() = nullptr;
    void (*ChangedText)() = nullptr;

protected:
    // Ŭ������
    bool isClicked = false;
    bool isLButtonDown = false;
    bool isHover = false;
    bool isLeave = false;

    
private:
    WCHAR oldText[64] = {};
};

