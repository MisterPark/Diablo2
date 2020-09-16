#include "pch.h"
#include "Cursor.h"
#include "Item.h"
#include "Inventory.h"

Cursor* pCursor = nullptr;

Cursor::Cursor()
{
    anim->SetSpriteKey(SpriteType::UI_CURSOR);
    anim->SetLoop(true);
    ShowCursor(FALSE);
}

Cursor::~Cursor()
{
    ShowCursor(TRUE);
}

Cursor* Cursor::GetInstance()
{
    if (pCursor == nullptr)
    {
        pCursor = new Cursor();
    }
    return pCursor;
}

void Cursor::Destroy()
{
    delete pCursor;
}

void Cursor::Update()
{
    transform.position = InputManager::GetMousePosOnClient();


    anim->Update();
}

void Cursor::Render()
{
    if (item == nullptr)
    {
        D2DRenderManager::DrawUI(anim->GetSpriteKey(), transform.position, anim->GetCurrentFrame());

    }
    else
    {
        D2DRenderManager::DrawUI(item->invenSprite, transform.position, 0);
    }
}

bool Cursor::HasItem()
{
    return (pCursor->item != nullptr);
}

bool Cursor::PickUpItem(Item* _item)
{
    if (pCursor->item != nullptr)return false;
    pCursor->item = _item;
    return true;
}

Item* Cursor::DropItem()
{
    Item* drop = pCursor->item;
    pCursor->item = nullptr;
    return drop;
}

Item* Cursor::GetItem()
{
    return pCursor->item;
}

bool Cursor::IsOnUI()
{
    Vector3 pos = pCursor->transform.position;
    if (Inventory::GetInstance()->isVisible)
    {
        RECT rt = Inventory::GetInstance()->area;
        if (pos.x > rt.left && pos.x <rt.right && pos.y > rt.top && pos.y < rt.bottom)
        {
            return true;
        }
    }
    return false;
}
