#include "pch.h"
#include "RenderManager.h"

RenderManager* pRenderManager = nullptr;

RenderManager::RenderManager()
{
	// 백버퍼 세팅
	hdc = GetDC(g_hwnd);
	hBackBitmap = CreateCompatibleBitmap(hdc, dfCLIENT_WIDTH, dfCLIENT_HEIGHT);
	hBackBufferDC = CreateCompatibleDC(hdc);
	SelectObject(hBackBufferDC, hBackBitmap);
	SetBkMode(hBackBufferDC, TRANSPARENT);
	SetStretchBltMode(hdc, COLORONCOLOR);
	// 스프라이트 배열 세팅
	pSprite = new Sprite[MaxOfEnum<SpriteIndex>()];
	// 스프라이트용 백버퍼
	width = dfCLIENT_WIDTH;
	height = dfCLIENT_HEIGHT;
	bitCount = 32;
	pitch = ((width * (bitCount >>3)) + 3) & ~3;
}

RenderManager::~RenderManager()
{
	// 백버퍼 해제
	ReleaseDC(g_hwnd, hdc);
	//일단 해제해 주고
	if (hBackBufferDC != nullptr)
	{
		SelectObject(hBackBufferDC, nullptr);
		DeleteDC(hBackBufferDC);
	}
	//백버퍼도 지운다.
	if (hBackBitmap != nullptr)
	{
		DeleteObject(hBackBitmap);
	}

	// 스프라이트 메모리 해제
	for (int index = 0; index < MaxOfEnum<SpriteIndex>(); index++)
	{
		ReleaseSprite(index);
	}
	delete[] pSprite;
	pSprite = nullptr;
}

RenderManager * RenderManager::GetInstance()
{
	if (pRenderManager == nullptr)
	{
		pRenderManager = new RenderManager;
	}
	return pRenderManager;
}

void RenderManager::Release()
{
	delete pRenderManager;
	pRenderManager = nullptr;
}

void RenderManager::Present()
{
	BitBlt(pRenderManager->hdc, 0, 0, dfCLIENT_WIDTH, dfCLIENT_HEIGHT,
		pRenderManager->hBackBufferDC, 0, 0, SRCCOPY);
}

void RenderManager::Clear()
{
	FillRect(pRenderManager->hBackBufferDC, &pRenderManager->area,
		(HBRUSH)GetStockObject(BLACK_BRUSH));
}


bool RenderManager::GetSpriteSize(SpriteIndex _index, int* _outW, int* _outH)
{
	int index = (int)_index;
	if (index >= (int)SpriteIndex::END || index < 0) return false;
	if (_outW == nullptr)return false;
	if (_outH == nullptr)return false;
	BITMAP bmp;
	GetObject(pRenderManager->pSprite[index].hBitmap, sizeof(BITMAP), &bmp);
	*_outW = bmp.bmWidth;
	*_outH = bmp.bmHeight;

	return true;
}

bool RenderManager::GetSpriteCenter(SpriteIndex _index, int* _outX, int* _outY)
{
	int index = (int)_index;
	if (index >= (int)SpriteIndex::END || index < 0) return false;
	if (_outX == nullptr)return false;
	if (_outY == nullptr)return false;

	*_outX = pRenderManager->pSprite[index].centerX;
	*_outY = pRenderManager->pSprite[index].centerY;

	return true;
}

int RenderManager::GetWidth()
{
	return pRenderManager->width;
}

int RenderManager::GetHeight()
{
	return pRenderManager->height;
}

void RenderManager::SetBufferSize(int _w, int _h)
{
	if (_w > dfCLIENT_WIDTH) return;
	if (_h > dfCLIENT_HEIGHT)return;

	pRenderManager->width = _w;
	pRenderManager->height = _h;
	//pRenderManager->pitch = ((_w * (32 >> 3)) + 3) & ~3;

}

void RenderManager::SetClientSize(int _w, int _h)
{
	pRenderManager->clientWidth = _w;
	pRenderManager->clientHeight = _h;
}


void RenderManager::DrawRect(const RECT& _rc)
{
	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void RenderManager::DrawRect(const RECT& _rc, COLORREF _innerColor)
{
	HBRUSH hBrush = CreateSolidBrush(_innerColor);
	HGDIOBJ oldBrush = SelectObject(pRenderManager->hBackBufferDC, hBrush);
	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	SelectObject(pRenderManager->hBackBufferDC, oldBrush);
	DeleteObject(hBrush);
}

void RenderManager::DrawRect(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor)
{
	HBRUSH hBrush = CreateSolidBrush(_innerColor);
	HPEN hPen = CreatePen(PS_SOLID, 1, _outlineColor);
	HGDIOBJ oldBrush = SelectObject(pRenderManager->hBackBufferDC, hBrush);
	HGDIOBJ oldPen = SelectObject(pRenderManager->hBackBufferDC, hPen);
	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	SelectObject(pRenderManager->hBackBufferDC, oldBrush);
	SelectObject(pRenderManager->hBackBufferDC, oldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void RenderManager::DrawSimpleCollider(const RECT& _rc, COLORREF _outlineColor)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, _outlineColor);
	HGDIOBJ oldPen = SelectObject(pRenderManager->hBackBufferDC, hPen);
	//Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	POINT pt;
	MoveToEx(pRenderManager->hBackBufferDC, _rc.left, _rc.top, &pt);
	LineTo(pRenderManager->hBackBufferDC, _rc.right, _rc.top);
	LineTo(pRenderManager->hBackBufferDC, _rc.right, _rc.bottom);
	LineTo(pRenderManager->hBackBufferDC, _rc.left, _rc.bottom);
	LineTo(pRenderManager->hBackBufferDC, _rc.left, _rc.top);

	SelectObject(pRenderManager->hBackBufferDC, oldPen);
	DeleteObject(hPen);
}

void RenderManager::DrawCircle(const RECT& _rc)
{
	Ellipse(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void RenderManager::DrawCircle(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor)
{
	HBRUSH hBrush = CreateSolidBrush(_innerColor);
	HPEN hPen = CreatePen(PS_SOLID, 1, _outlineColor);
	HGDIOBJ oldBrush = SelectObject(pRenderManager->hBackBufferDC, hBrush);
	HGDIOBJ oldPen = SelectObject(pRenderManager->hBackBufferDC, hPen);
	Ellipse(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	SelectObject(pRenderManager->hBackBufferDC, oldBrush);
	SelectObject(pRenderManager->hBackBufferDC, oldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void RenderManager::DrawString(const WCHAR* _str, int _x, int _y)
{
	TextOutW(pRenderManager->hBackBufferDC, _x, _y, _str, wcslen(_str));
}

void RenderManager::DrawString(const WCHAR* _str, int _x, int _y, COLORREF _color)
{
	COLORREF oldColor = SetTextColor(pRenderManager->hBackBufferDC, _color);
	TextOutW(pRenderManager->hBackBufferDC, _x, _y, _str, wcslen(_str));
	SetTextColor(pRenderManager->hBackBufferDC, oldColor);
}

void RenderManager::DrawString(const WCHAR * _str, int _x, int _y, int _fontSize, COLORREF _color)
{
	HFONT hFont = CreateFont(_fontSize, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, NULL);
	HFONT oldFont = (HFONT)SelectObject(pRenderManager->hBackBufferDC, hFont);
	COLORREF oldColor = SetTextColor(pRenderManager->hBackBufferDC, _color);
	TextOutW(pRenderManager->hBackBufferDC, _x, _y, _str, wcslen(_str));
	SelectObject(pRenderManager->hBackBufferDC, oldFont);
	DeleteObject(hFont);
	SetTextColor(pRenderManager->hBackBufferDC, oldColor);
}

void RenderManager::DrawString(const WCHAR* _str, int _x, int _y, const WCHAR* _font, int _fontSize, COLORREF _color)
{
	HFONT hFont = CreateFont(_fontSize, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, _font);
	HFONT oldFont = (HFONT)SelectObject(pRenderManager->hBackBufferDC, hFont);
	COLORREF oldColor = SetTextColor(pRenderManager->hBackBufferDC, _color);
	TextOutW(pRenderManager->hBackBufferDC, _x, _y, _str, wcslen(_str));
	SelectObject(pRenderManager->hBackBufferDC, oldFont);
	DeleteObject(hFont);
	SetTextColor(pRenderManager->hBackBufferDC, oldColor);
}

void RenderManager::DrawLine(float _startX, float _startY, float _endX, float _endY)
{
	POINT pt = {};
	MoveToEx(pRenderManager->hBackBufferDC, _startX, _startY, &pt);
	LineTo(pRenderManager->hBackBufferDC, _endX, _endY);
}

void RenderManager::DrawLine(float _startX, float _startY, float _endX, float _endY, COLORREF _color)
{
	POINT pt = {};
	HPEN hPen = CreatePen(PS_SOLID, 1, _color);
	HGDIOBJ oldPen = SelectObject(pRenderManager->hBackBufferDC, hPen);
	MoveToEx(pRenderManager->hBackBufferDC, _startX, _startY, &pt);
	LineTo(pRenderManager->hBackBufferDC, _endX, _endY);
	SelectObject(pRenderManager->hBackBufferDC, oldPen);
	DeleteObject(hPen);
}

bool RenderManager::LoadSprite(SpriteIndex _index, const char* _fileName, int _centerX, int _centerY)
{
	if (MaxOfEnum<SpriteIndex>() <= (int)_index)
	{
		return false;
	}
	if (pRenderManager->pSprite[(int)_index].hBitmap != INVALID_HANDLE_VALUE)
	{
		return false;
	}

	HBITMAP hBitmap;
	BITMAP bmp;
	HDC hMemDC = CreateCompatibleDC(pRenderManager->hBackBufferDC);

	hBitmap = (HBITMAP)LoadImageA(NULL, _fileName,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	if (hBitmap == INVALID_HANDLE_VALUE)
	{
		ReleaseDC(g_hwnd, hMemDC);
		return false;
	}
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	pRenderManager->pSprite[(int)_index].hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	pRenderManager->pSprite[(int)_index].memDC = hMemDC;
	pRenderManager->pSprite[(int)_index].hBitmap = hBitmap;
	pRenderManager->pSprite[(int)_index].width = bmp.bmWidth;
	pRenderManager->pSprite[(int)_index].height = bmp.bmHeight;
	pRenderManager->pSprite[(int)_index].centerX = _centerX;
	pRenderManager->pSprite[(int)_index].centerY = _centerY;
	pRenderManager->pSprite[(int)_index].isLoaded = true;

	return true;

}

void RenderManager::ReleaseSprite(int _index)
{
	//최대 할당된 스프라이트를 넘어서면 리턴
	if (MaxOfEnum<SpriteIndex>() <= _index) return;
	if (!pRenderManager->pSprite[_index].isLoaded) return;

	Sprite* sprite = &pRenderManager->pSprite[_index];
	SelectObject(sprite->memDC, sprite->hOldBitmap);
	DeleteObject(sprite->hBitmap);
	DeleteDC(sprite->memDC);
}

void RenderManager::DrawSprite(SpriteType _type, SpriteIndex _index, int destX, int destY)
{
	//최대 스프라이트 갯수 초과
	if (MaxOfEnum<SpriteIndex>() <= (int)_index) return;
	//로드되지 않는 스프라이트
	if (pRenderManager->pSprite[(int)_index].isLoaded == false) return;

	Sprite* sprite = &pRenderManager->pSprite[(int)_index];

	TransparentBlt(pRenderManager->hBackBufferDC,
		destX - sprite->centerX, destY -sprite->centerY, sprite->width, sprite->height,
		sprite->memDC, 0, 0, sprite->width, sprite->height, pRenderManager->colorKey);

}

void RenderManager::DrawSprite(SpriteType _type, SpriteIndex _index, int destX, int destY, int destW, int destH)
{
	//최대 스프라이트 갯수 초과
	if (MaxOfEnum<SpriteIndex>() <= (int)_index) return;
	//로드되지 않는 스프라이트
	if (pRenderManager->pSprite[(int)_index].isLoaded == false) return;

	Sprite* sprite = &pRenderManager->pSprite[(int)_index];

	TransparentBlt(pRenderManager->hBackBufferDC,
		destX - sprite->centerX, destY - sprite->centerY, destW, destH,
		sprite->memDC, 0, 0, sprite->width, sprite->height, pRenderManager->colorKey);
}

void RenderManager::DrawTile(SpriteType _type, SpriteIndex _index, int _tileOffset, int destX, int destY)
{
	//최대 스프라이트 갯수 초과
	if (MaxOfEnum<SpriteIndex>() <= (int)_index) return;
	//로드되지 않는 스프라이트
	if (pRenderManager->pSprite[(int)_index].isLoaded == false) return;

	Sprite* sprite = &pRenderManager->pSprite[(int)_index];

	int tileX = sprite->width / dfTILE_W; // 타일 열개수
	int tileY = sprite->height / dfTILE_H; // 타일 행개수 (필요가 없는듯?)
	int row = _tileOffset / tileX; // 타일 행번호
	int col = _tileOffset % tileX; // 타일 열번호

	TransparentBlt(pRenderManager->hBackBufferDC,
		destX - sprite->centerX, destY - sprite->centerY,
		dfTILE_W, dfTILE_H,
		sprite->memDC, col*dfTILE_W, row*dfTILE_H, dfTILE_W, dfTILE_H, pRenderManager->colorKey);
}

void RenderManager::DrawImage(SpriteIndex _index, int destX, int destY, int len)
{
	//최대 스프라이트 갯수 초과
	if (MaxOfEnum<SpriteIndex>() <= (int)_index)
	{
		return;
	}

	//로드되지 않는 스프라이트
	if (pRenderManager->pSprite[(int)_index].isLoaded == false)
	{
		return;
	}

	Sprite* sprite = &pRenderManager->pSprite[(int)_index];

	TransparentBlt(pRenderManager->hBackBufferDC,
		destX, destY, sprite->width, sprite->height,
		sprite->memDC, 0, 0, sprite->width, sprite->height, pRenderManager->colorKey);

}

void RenderManager::Flip()
{
	
	//StretchDIBits(pRenderManager->hdc,
	//	0, 0, pRenderManager->clientWidth, pRenderManager->clientHeight,
	//	0, 0, pRenderManager->width, pRenderManager->height, pRenderManager->buffer,
	//	&pRenderManager->backBufferInfo, DIB_RGB_COLORS, SRCCOPY);

	StretchBlt(pRenderManager->hdc,
		0, 0, pRenderManager->clientWidth, pRenderManager->clientHeight,
		pRenderManager->hBackBufferDC,
		0, 0, pRenderManager->width, pRenderManager->height,
		SRCCOPY);

}
