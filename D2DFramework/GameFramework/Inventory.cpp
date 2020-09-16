#include "pch.h"
#include "Inventory.h"
#include "Button.h"
#include "Cursor.h"

Inventory* pInventory = nullptr;

Inventory::Inventory()
{
    anim->SetSpriteKey(SpriteType::UI_PANEL_INVEN);
    transform.position.x = 400;
    transform.position.y = 62;
    isVisible = false;
    isEnable = false;

    area.left = 400;
    area.right = dfCLIENT_WIDTH;
    area.top = 0;
    area.bottom = dfCLIENT_HEIGHT;

    // 버튼
    exitBtn = new Button();
    exitBtn->SetSpriteImage(SpriteType::UI_BTN_BUYSELL);
    exitBtn->spriteIndex = 10;
    exitBtn->transform.position = { 418,446,0 };
    exitBtn->Click = Exit;
}

Inventory::~Inventory()
{
    delete exitBtn;
}

Inventory* Inventory::GetInstance()
{
    if (pInventory == nullptr)
    {
        pInventory = new Inventory;
    }
    return pInventory;
}

void Inventory::Destroy()
{
    delete pInventory;
}

void Inventory::Update()
{
    if (InputManager::GetKeyDown('I'))
    {
        isVisible = !isVisible;
        isEnable = !isEnable;
    }
    if (InputManager::GetKeyDown(VK_ESCAPE))
    {
        isVisible = false;
        isEnable = false;
    }

    if (isEnable == false) return;
    if (InputManager::GetMouseLButtonDown())
    {
        Vector3 cursorPos = Cursor::GetInstance()->transform.position;
        int row, col;
        if (GetSlotIndex(cursorPos, &row, &col)) // 슬롯 안에 클릭시
        {
            if (Cursor::HasItem()) // 커서가 아이템을 가진 경우
            {
                Item* exist = nullptr;
                if (IsAbleToInsert(row, col, Cursor::GetItem(), &exist)) // 아이템이 들어갈 수 있다면
                {
                    if (exist == nullptr) // 뺄 아이템이 없는 경우
                    {
                        RegisterItem(row, col, Cursor::DropItem()); // 커서에서 삭제후 등록
                    }
                    else // 뺼 아이템이 있는 경우
                    {
                        UnregisterItem(exist); // 기존아이템 제거
                        RegisterItem(row, col, Cursor::DropItem()); // 커서에서 삭제후 등록
                        Cursor::PickUpItem(exist); // 커서가 기존 아이템 소유
                    }
                    
                }
            }
            else // 커서가 아이템을 갖지 않은 경우
            {
                Item* item = GetItem(row, col);
                if (item != nullptr)
                {
                    UnregisterItem(row, col);
                    Cursor::PickUpItem(item);
                }
            }
        }
    }
    exitBtn->Update();
}

void Inventory::Render()
{
    if (isVisible == false) return;

    D2DRenderManager::DrawUI(SpriteType::UI_PANEL_800R, Vector3(400, -2, 0), 0);
    D2DRenderManager::DrawUI(anim->GetSpriteKey(), transform.position, 0);

    for (auto& item : itemList)
    {
        Vector3 pos;
        pos.x = dfSLOT_X + item->slotX * dfITEM_INVEN_W;
        pos.y = dfSLOT_Y + item->slotY * dfITEM_INVEN_H;
        D2DRenderManager::DrawUI(item->invenSprite, pos, 0);
    }

    exitBtn->Render();
}

void Inventory::Exit()
{
    pInventory->isVisible = false;
    pInventory->isEnable = false;
}

bool Inventory::Insert(Item* item)
{
    if (item == nullptr) return false;
    

    for (int row = 0; row < dfSLOT_ROW_COUNT; row++)
    {
        for (int col = 0; col < dfSLOT_COL_COUNT; col++)
        {
            int maxRow = row + item->slotH;
            int maxCol = col + item-> slotW;
            if (maxRow > dfSLOT_ROW_COUNT) return false;
            if (maxCol > dfSLOT_COL_COUNT) return false;
            if (IsEmptySlot(row, col, item))
            {
                RegisterItem(row, col, item);
                return true;
            }

            
        }
    }


    return false;
}

bool Inventory::Drop(Item* item)
{
    return false;
}

bool Inventory::IsEmptySlot(int row, int col, Item* item)
{
    int maxRow = row + item->slotH;
    int maxCol = col + item->slotW;
    for (int i = row; i < maxRow; i++)
    {
        for (int j = col; j < maxCol; j++)
        {
            if (pInventory->slots[i][j] != nullptr)
            {
                return false;
            }
        }
    }
    return true;
}

void Inventory::RegisterItem(int row, int col, Item* item)
{
    int maxRow = row + item->slotH;
    int maxCol = col + item->slotW;
    item->slotX = col;
    item->slotY = row;
    for (int i = row; i < maxRow; i++)
    {
        for (int j = col; j < maxCol; j++)
        {
            pInventory->slots[i][j] = item;
        }
    }
    item->isEnable = false;
    item->isVisible = false;
    pInventory->itemList.push_back(item);
}

Item* Inventory::UnregisterItem(int row, int col)
{
    Item* item = pInventory->slots[row][col];
    if (item == nullptr) return nullptr;
    int maxRow = item->slotY + item->slotH;
    int maxCol = item->slotX + item->slotW;
    for (int i = item->slotY; i < maxRow; i++)
    {
        for (int j = item->slotX; j < maxCol; j++)
        {
            pInventory->slots[i][j] = nullptr;
        }
    }
    pInventory->itemList.remove(item);
    return item;
}

Item* Inventory::UnregisterItem(Item* item)
{
    for (int i = 0; i < dfSLOT_ROW_COUNT; i++)
    {
        for (int j = 0; j < dfSLOT_COL_COUNT; j++)
        {
            if (pInventory->slots[i][j] == item)
            {
                pInventory->slots[i][j] = nullptr;
            }
        }
    }
    pInventory->itemList.remove(item);
    return nullptr;
}

bool Inventory::GetSlotIndex(const Vector3& cursor, int* outRow, int* outCol)
{
    int sx = dfSLOT_X;
    int sy = dfSLOT_Y;
    int ex = sx + dfSLOT_COL_COUNT * dfITEM_INVEN_W;
    int ey = sy + dfSLOT_ROW_COUNT * dfITEM_INVEN_H;
    if (cursor.x < sx)return false;
    if (cursor.x > ex)return false;
    if (cursor.y < sy)return false;
    if (cursor.y > ey)return false;

    int col = (cursor.x - sx) / dfITEM_INVEN_W;
    int row = (cursor.y - sy) / dfITEM_INVEN_H;

    *outRow = row;
    *outCol = col;

    return true;
}

Item* Inventory::GetItem(int row, int col)
{
    return pInventory->slots[row][col];
}

bool Inventory::IsAbleToInsert(int row, int col, Item* InsertItem, Item** outItem)
{
    if (row < 0)return false;
    if (col < 0)return false;
    if (row >= dfSLOT_ROW_COUNT) return false;
    if (col >= dfSLOT_COL_COUNT) return false;
    if (row + InsertItem->slotH > dfSLOT_ROW_COUNT) return false;
    if (col + InsertItem->slotW > dfSLOT_COL_COUNT) return false;

    Item* exist = nullptr;
    int maxRow = row + InsertItem->slotH;
    int maxCol = col + InsertItem->slotW;
    for (int i = row; i < maxRow; i++)
    {
        for (int j = col; j < maxCol; j++)
        {
            if (pInventory->slots[i][j] == nullptr) continue;
            if (exist != pInventory->slots[i][j] && exist != nullptr) return false;
            exist = pInventory->slots[i][j];
        }
    }

    *outItem = exist;
    return true;
}
