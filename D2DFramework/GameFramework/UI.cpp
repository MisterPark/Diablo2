#include "pch.h"
#include "UI.h"

void UI::Update()
{
	anim->Update();
}

void UI::Render()
{
	D2DRenderManager::DrawUI(anim->GetSpriteKey(), transform.position, 0);
}

void UI::UpdateUI()
{
	area.left = transform.position.x;
	area.top = transform.position.y;
	Texture* tex = D2DRenderManager::GetTexture(sprite);
	if (tex != nullptr)
	{
		area.right = area.left + tex->GetSpriteWidth();
		area.bottom = area.top + tex->GetSpriteHeight();
	}

	UpdateEvent();
	
}

int UI::X()
{
	return transform.position.x;
}

int UI::Y()
{
	return transform.position.y;
}

int UI::Width()
{
	Texture* tex = D2DRenderManager::GetTexture(sprite);
	return tex->GetSpriteWidth();
}

int UI::Height()
{
	Texture* tex = D2DRenderManager::GetTexture(sprite);
	return tex->GetSpriteHeight();
}

void UI::SetSpriteImage(SpriteType _type)
{
	sprite = _type;
	Texture* tex = D2DRenderManager::GetTexture(sprite);
	if (tex != nullptr)
	{
		area.left = transform.position.x;
		area.top = transform.position.y;
		area.right = area.left + tex->GetSpriteWidth();
		area.bottom = area.top + tex->GetSpriteHeight();
	}
}

void UI::SetText(const wstring& _text)
{
	wmemset(text, 0, 64);
	wmemcpy(text, _text.c_str(), lstrlenW(_text.c_str()));
}

void UI::SetText(int _val)
{
	WCHAR t[16] = {};
	swprintf_s(t, L"%d", _val);
	wmemcpy(text, t, lstrlenW(t));
}

void UI::SetText(int _val1, int _val2)
{
	WCHAR t[32] = {};
	swprintf_s(t, L"%d - %d", _val1, _val2);
	wmemcpy(text, t, lstrlenW(t));
}

void UI::ClearEvent()
{
	isClicked = false;
	isLButtonDown = false;
	isHover = false;
	isLeave = false;
}

void UI::UpdateEvent()
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

	if (lstrcmpW(text, oldText) != 0)
	{
		lstrcpyW(oldText, text);
		OnChangedText();
	}
}

void UI::OnClick()
{
	if (Click != nullptr)
	{
		Click();
	}
}

void UI::OnLButtonDown()
{
	if (LButtonDown != nullptr)
	{
		LButtonDown();
	}
}

void UI::OnLButtonUp()
{
	if (LButtonUp != nullptr)
	{
		LButtonUp();
	}
}

void UI::OnHover()
{
	if (Hover != nullptr)
	{
		Hover();
	}
}

void UI::OnLeave()
{
	if (Leave != nullptr)
	{
		Leave();
	}
}

void UI::OnChangedText()
{
	if (ChangedText != nullptr)
	{
		ChangedText();
	}
}
