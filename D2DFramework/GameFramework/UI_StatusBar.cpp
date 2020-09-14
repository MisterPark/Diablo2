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

	if (Player::GetInstance()->pChar == nullptr) return;
	SetHPPercent(Player::GetInstance()->pChar->stat[(int)StatType::MAX_LIFE], Player::GetInstance()->pChar->stat[(int)StatType::LIFE]);
	SetMPPercent(Player::GetInstance()->pChar->stat[(int)StatType::MAX_MANA], Player::GetInstance()->pChar->stat[(int)StatType::MANA]);

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
	if (max == 0 || hp ==0)
	{
		pBar->perHP = 0.f;
		return;
	}
	pBar->perHP = (float)hp / max;
}

void UI_StatusBar::SetMPPercent(int max, int mp)
{
	if (max == 0 || mp == 0)
	{
		pBar->perMP = 0.f;
		return;
	}
	pBar->perMP = (float)mp / max;
}
