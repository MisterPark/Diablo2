#include "pch.h"
#include "UI_StatusBar.h"

UI_StatusBar* pBar = nullptr;

UI_StatusBar::UI_StatusBar()
{
	isVisible = false;
	anim->SetSpriteKey(SpriteType::UI_PANEL_STATUS_BAR);
	transform.position.y = dfCLIENT_HEIGHT - 103;
}

UI_StatusBar::~UI_StatusBar()
{
}

UI_StatusBar* UI_StatusBar::GetInstance()
{
	if (pBar == nullptr)
	{
		pBar = new UI_StatusBar;
	}
	return pBar;
}

void UI_StatusBar::Destroy()
{
	delete pBar;
}

void UI_StatusBar::Update()
{
	anim->Update();
}

void UI_StatusBar::Render()
{
	if (isVisible == false)return;
	anim->RenderImage();

	D2DRenderManager::DrawImage(SpriteType::UI_HP_BALL, 30, 507, perHP);
	D2DRenderManager::DrawImage(SpriteType::UI_MP_BALL, 690, 507, perMP);

}

void UI_StatusBar::OnClick()
{
}

void UI_StatusBar::OnLButtonDown()
{
}

void UI_StatusBar::OnLButtonUp()
{
}

void UI_StatusBar::OnHover()
{
}

void UI_StatusBar::OnLeave()
{
}

void UI_StatusBar::OnChangedText()
{
}

void UI_StatusBar::SetHPPercent(int max, int hp)
{
	pBar->perHP = (float)hp / max;
}

void UI_StatusBar::SetMPPercent(int max, int mp)
{
	pBar->perMP = (float)mp / max;
}
