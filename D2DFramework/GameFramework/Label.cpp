#include "pch.h"
#include "Label.h"

Label::Label()
{
	SetFont(L"µ¸¿ò", 11, FW_BOLD);
}

Label::~Label()
{
	if (pFont)
	{
		pFont->Release();
		pFont = nullptr;
	}
}

void Label::Update()
{
	UpdateUI();
}

void Label::Render()
{
	if (isDrawRect)
	{
		float sx = transform.position.x - 5;
		float sy = transform.position.y - 5;
		float ex = transform.position.x + Width() + 5;
		float ey = transform.position.y + Height() + 5;
		D2DRenderManager::DrawRect(sx, sy, ex, ey);
	}
	D2DRenderManager::DrawString(pFont, text, transform.position.x, transform.position.y, color);
	
}

void Label::OnClick()
{
	
}

void Label::OnLButtonDown()
{
}

void Label::OnLButtonUp()
{
}

void Label::OnHover()
{
}

void Label::OnLeave()
{
}

void Label::OnChangedText()
{
}

int Label::Width()
{
	if (pFont == nullptr) return 0;
	TEXTMETRICW tm = {};
	pFont->GetTextMetricsW(&tm);
	int w = tm.tmAveCharWidth * lstrlenW(text)*2;
	return w;
}

int Label::Height()
{
	if (pFont == nullptr) return 0;
	TEXTMETRICW tm = {};
	pFont->GetTextMetricsW(&tm);
	return tm.tmHeight;
}

void Label::SetFont(const wstring& faceName, int size, UINT fontWeight)
{
	if (pFont)
	{
		pFont->Release();
		pFont = nullptr;
	}
	this->size = size;
	this->fontWeight = fontWeight;

	D3DXFONT_DESCW fontInfo;
	ZeroMemory(&fontInfo, sizeof(D3DXFONT_DESCW));
	fontInfo.Height = size;
	fontInfo.Width = 0;
	fontInfo.Weight = fontWeight;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"µ¸¿ò");
	if (FAILED(D3DXCreateFontIndirect(D2DRenderManager::GetDevice(), &fontInfo, &pFont)))
	{
		throw "ÆùÆ® »ý¼º ½ÇÆÐ";
	}
}

void Label::SetColor(D3DXCOLOR color)
{
	this->color = color;
}

void Label::SetRect(bool _isDrawRect)
{
	this->isDrawRect = _isDrawRect;
}
