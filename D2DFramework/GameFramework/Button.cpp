#include "pch.h"
#include "Button.h"
#include "Label.h"

Button::Button()
{
	pLabel = new Label();
}

Button::~Button()
{
	delete pLabel;
}

void Button::Update()
{
	UpdateUI();

}

void Button::Render()
{
	D2DRenderManager::DrawUI(sprite, transform, drawIndex);

	pLabel->transform.position.x = transform.position.x + ((Width() - pLabel->Width()) / 2) - 15;
	pLabel->transform.position.y = transform.position.y + ((Height() - pLabel->Height()) / 2);
	pLabel->Render();

	//D2DRenderManager::DrawLine(area.left, area.top, area.right, area.top, D3DCOLOR_ARGB(255, 0, 255, 0));
	//D2DRenderManager::DrawLine(area.right, area.top, area.right, area.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
	//D2DRenderManager::DrawLine(area.left, area.bottom, area.right, area.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
	//D2DRenderManager::DrawLine(area.left, area.top, area.left, area.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
	
}

void Button::OnClick()
{
	UI::OnClick();
}

void Button::OnLButtonDown()
{
	UI::OnLButtonDown();
	drawIndex = spriteIndex + 1;
}

void Button::OnLButtonUp()
{
	UI::OnLButtonUp();
	drawIndex = spriteIndex;
}

void Button::OnHover()
{
	UI::OnHover();
}

void Button::OnLeave()
{
	UI::OnLeave();
	drawIndex = spriteIndex;
}

void Button::OnChangedText()
{
	UI::OnChangedText();
	pLabel->SetText(text);
}

void Button::SetFont(const wstring& faceName, int size, UINT fontWeight)
{
	if (pLabel == nullptr) return;
	pLabel->SetFont(faceName, size, fontWeight);
}
