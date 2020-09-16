#pragma once
#include "UI.h"
#include "Item.h"

#define dfSLOT_ROW_COUNT 4
#define dfSLOT_COL_COUNT 10
#define dfSLOT_X 418
#define dfSLOT_Y 318

class Button;

class Inventory : public UI
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

    static void Exit();
    // 빈슬롯 찾아서 무작위로 넣음
    static bool Insert(Item* item);
    static bool Drop(Item* item);
    static bool IsEmptySlot(int row, int col, Item* item);

    static void RegisterItem(int row, int col, Item* item);
    static Item* UnregisterItem(int row, int col);
    static Item* UnregisterItem(Item* item);

    static bool GetSlotIndex(const Vector3& cursor, int* outRow, int* outCol);
    static Item* GetItem(int row, int col);
    static bool IsAbleToInsert(int row, int col, Item* InsertItem, Item** outItem);

    
    Button* exitBtn = nullptr;
    list<Item*> itemList;
    Item* slots[dfSLOT_ROW_COUNT][dfSLOT_COL_COUNT] = {};
};

