#include "pch.h"
#include "Panel_Status.h"

Panel_Status* pStatusPanel = nullptr;

Panel_Status::Panel_Status()
{
	anim->SetSpriteKey(SpriteType::UI_PANEL_STATUS);
	transform.position.x = 80;
	transform.position.y = 62;
	isVisible = false;
}

Panel_Status::~Panel_Status()
{
}

Panel_Status* Panel_Status::GetInstance()
{
	if (pStatusPanel == nullptr)
	{
		pStatusPanel = new Panel_Status;
	}
	return pStatusPanel;
}

void Panel_Status::Destroy()
{
	delete pStatusPanel;
}

void Panel_Status::Update()
{
	if (InputManager::GetKeyDown('A'))
	{
		isVisible = !isVisible;
	}
	if (InputManager::GetKeyDown(VK_ESCAPE))
	{
		isVisible = false;
	}
}

void Panel_Status::Render()
{
	if (isVisible == false)return;
	D2DRenderManager::DrawUI(SpriteType::UI_PANEL_800L, Vector3(0,-2,0), 0);
	anim->RenderImage();
}

void Panel_Status::OnClick()
{
}

void Panel_Status::OnLButtonDown()
{
}

void Panel_Status::OnLButtonUp()
{
}

void Panel_Status::OnHover()
{
}

void Panel_Status::OnLeave()
{
}

void Panel_Status::OnChangedText()
{
}
