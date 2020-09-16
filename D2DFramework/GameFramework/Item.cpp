#include "pch.h"
#include "Item.h"
#include "Inventory.h"

Item::Item()
{
	anim->SetDelay(0.05f);

	label = new Label;
	label->SetColor(Color(255, 250, 250, 250));
	label->SetFont(L"µ¸¿ò", 11, 0);
	label->SetRect(true);
}

Item::~Item()
{
	delete label;
}

void Item::Update()
{
	if (isEnable == false) return;

	label->transform.position = transform.position - Camera::GetPosition();
	label->transform.position.x -= 20;
	label->transform.position.y -= 20;
	anim->Update();
	UpdateArea();
	UpdateEvent();
}

void Item::Render()
{
	if (isVisible == false) return;
	//D2DRenderManager::DrawSprite(anim->GetSpriteKey(), transform, anim->GetCurrentFrame());
	D2DRenderManager::DrawItem(anim->GetSpriteKey(), transform.position, anim->GetCurrentFrame());
	//D2DRenderManager::DrawLine(area.left, area.top, area.right, area.top, D3DCOLOR_ARGB(255, 0, 255, 0));
	//D2DRenderManager::DrawLine(area.right, area.top, area.right, area.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
	//D2DRenderManager::DrawLine(area.left, area.bottom, area.right, area.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
	//D2DRenderManager::DrawLine(area.left, area.top, area.left, area.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));

	if (InputManager::GetKey(VK_CONTROL))
	{
		label->Render();
	}
}

void Item::UpdateArea()
{
	float offsetX = Camera::GetX();
	float offsetY = Camera::GetY();
	area.left = transform.position.x - dfITEM_W/2- offsetX;
	area.top = transform.position.y - dfITEM_H/2-offsetY;
	area.right = area.left + dfITEM_W;
	area.bottom = area.top + dfITEM_H;
}

void Item::UpdateEvent()
{
	POINT pt = InputManager::GetMousePosOnClient();
	if (pt.x > area.left &&
		pt.x < area.right &&
		pt.y > area.top &&
		pt.y < area.bottom)
	{
		if (isHover == false)
		{
			OnHover();
		}
		isHover = true;
		isLeave = false;
	}
	else
	{
		if (isLeave == false)
		{
			OnLeave();
		}
		isHover = false;
		isLeave = true;
	}

	if (InputManager::GetMouseLButtonDown())
	{
		if (isHover)
		{
			isLButtonDown = true;
			OnLButtonDown();
		}
	}
	if (InputManager::GetMouseLButtonUp())
	{
		if (isHover)
		{
			OnLButtonUp();
			if (isLButtonDown)
			{
				OnClick();
			}
		}
		isLButtonDown = false;
	}
}


void Item::OnClick()
{
	if (Click != nullptr)
	{
		Click();
	}
}

void Item::OnLButtonDown()
{
	if (LButtonDown != nullptr)
	{
		LButtonDown();
	}

	if (Player::GetInstance()->pChar)
	{
		Vector3 pPos = Player::GetInstance()->pChar->transform.position;
		if (pPos.x < transform.position.x - dfITEM_W / 2) return;
		if (pPos.x > transform.position.x + dfITEM_W / 2) return;
		if (pPos.y < transform.position.y - dfITEM_H / 2) return;
		if (pPos.y > transform.position.y + dfITEM_H / 2) return;

		Inventory::Insert(this);
	}
}

void Item::OnLButtonUp()
{
	if (LButtonUp != nullptr)
	{
		LButtonUp();
	}
}

void Item::OnHover()
{
	if (Hover != nullptr)
	{
		Hover();
	}
}

void Item::OnLeave()
{
	if (Leave != nullptr)
	{
		Leave();
	}
}
