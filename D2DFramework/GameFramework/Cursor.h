#pragma once
#include "GameObject.h"
class Item;

class Cursor :
    public GameObject
{
private:
    Cursor();
    virtual ~Cursor();
public:
    static Cursor* GetInstance();
    static void Destroy();
    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;

    static bool HasItem();
    static bool PickUpItem(Item* _item);
    static Item* DropItem();
    static Item* GetItem();

    static bool IsOnUI();
private:

    Item* item = nullptr;
};

