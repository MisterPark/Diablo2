#include "pch.h"
#include "Inventory.h"

Inventory* pInventory = nullptr;

Inventory::Inventory()
{
    anim->SetSpriteKey(SpriteType::UI_PANEL_INVEN);
    transform.position.x = 400;
    transform.position.y = 62;
    isVisible = false;
}

Inventory::~Inventory()
{
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
    }
    if (InputManager::GetKeyDown(VK_ESCAPE))
    {
        isVisible = false;
    }
}

void Inventory::Render()
{
    if (isVisible == false) return;

    D2DRenderManager::DrawUI(SpriteType::UI_PANEL_800R, Vector3(400, -2, 0), 0);
    anim->RenderImage();
}

void Inventory::OnClick()
{
}

void Inventory::OnLButtonDown()
{
}

void Inventory::OnLButtonUp()
{
}

void Inventory::OnHover()
{
}

void Inventory::OnLeave()
{
}

void Inventory::OnChangedText()
{
}
