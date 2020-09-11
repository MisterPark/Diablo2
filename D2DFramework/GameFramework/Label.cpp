#include "pch.h"
#include "Label.h"

Label::Label()
{
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
	int w = tm.tmAveCharWidth * lstrlenW(text);
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
	lstrcpy(fontInfo.FaceName, L"돋움");
	if (FAILED(D3DXCreateFontIndirect(D2DRenderManager::GetDevice(), &fontInfo, &pFont)))
	{
		throw "폰트 생성 실패";
	}
}

void Label::SetColor(D3DXCOLOR color)
{
	this->color = color;
}
