#pragma once
#include "GameObject.h"
#include "Label.h"

#define dfITEM_W 40
#define dfITEM_H 40
#define dfITEM_INVEN_W 29
#define dfITEM_INVEN_H 28


class Item :
    public GameObject
{
public:
    Item();
    virtual ~Item();

    // GameObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;

    void UpdateArea();
    void UpdateEvent();
    virtual void OnClick();
    virtual void OnLButtonDown();
    virtual void OnLButtonUp();
    virtual void OnHover();
    virtual void OnLeave();

    void (*Click)() = nullptr;
    void (*LButtonDown)() = nullptr;
    void (*LButtonUp)() = nullptr;
    void (*Hover)() = nullptr;
    void (*Leave)() = nullptr;
public:
    bool isClicked = false;
    bool isLButtonDown = false;
    bool isHover = false;
    bool isLeave = false;
    
    
    Label* label = nullptr;
    RECT area = {};

    SpriteType invenSprite = SpriteType::NONE;

    int slotX = 0;
    int slotY = 0;
    int slotW = 1;
    int slotH = 1;
};

