#pragma once
#include <Windows.h>

enum class SpriteIndex
{
	NONE,
	BACKGROUND,

	END,
};

enum class SpriteType
{
	NORMAL = 0,
	TONEDOWN_RED,
	TONEDOWN_GREEN,
	TONEDOWN_BLUE,
	TONEUP_RED,
	TONEUP_GREEN,
	TONEUP_BLUE,
	ALPHA50,
	CLOAKING,
	TRANSPARENTS,

	END
};

typedef struct Sprite
{
	HDC memDC;
	HBITMAP hBitmap = (HBITMAP)INVALID_HANDLE_VALUE;
	HBITMAP hOldBitmap = (HBITMAP)INVALID_HANDLE_VALUE;
	int width = 0;
	int height = 0;
	int centerX = 0;
	int centerY = 0;
	bool isLoaded = false;

}SPRITE;

class RenderManager
{
private:
	RenderManager();
	~RenderManager();

public:
	static RenderManager* GetInstance();
	static void Release();
	static void Present();
	static void Clear();

	static bool GetSpriteSize(SpriteIndex _index, int* _outW, int* _outH);
	static bool GetSpriteCenter(SpriteIndex _index, int* _outX, int* _outY);
	static int GetWidth();
	static int GetHeight();
	static void SetBufferSize(int _w, int _h);
	static void SetClientSize(int _w, int _h);


	// �⺻ ����
	static void DrawRect(const RECT& _rc);
	static void DrawRect(const RECT& _rc, COLORREF _innerColor);
	static void DrawRect(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor);
	static void DrawSimpleCollider(const RECT& _rc, COLORREF _outlineColor);
	static void DrawCircle(const RECT& _rc);
	static void DrawCircle(const RECT& _rc, COLORREF _innerColor, COLORREF _outlineColor);
	static void DrawString(const WCHAR* _str, int _x, int _y);
	static void DrawString(const WCHAR* _str, int _x, int _y, COLORREF _color);
	static void DrawString(const WCHAR* _str, int _x, int _y, int _fontSize, COLORREF _color);
	static void DrawString(const WCHAR* _str, int _x, int _y, const WCHAR* _font, int _fontSize, COLORREF _color);
	static void DrawLine(float _startX, float _startY, float _endX, float _endY);
	static void DrawLine(float _startX, float _startY, float _endX, float _endY, COLORREF _color);
	
	// �̹��� ��������Ʈ
	static bool LoadSprite(SpriteIndex _index, const char* _fileName, int _centerX, int _centerY);
	static void ReleaseSprite(int _index);
	static void DrawSprite(SpriteType _type, SpriteIndex _index, int destX, int destY);
	static void DrawSprite(SpriteType _type, SpriteIndex _index, int destX, int destY, int destW, int destH);
	static void DrawTile(SpriteType _type, SpriteIndex _index, int _tileOffset, int destX, int destY);
	//Ư�� �޸� ��ġ�� �̹����� ����Ѵ�(Ŭ���� ó��)
	static void DrawImage(SpriteIndex spriteIndex, int destX, int destY, int len = 100);
	// ���� ����
	static void Flip();

	
private:
	HDC hdc;
	HBITMAP hBackBitmap;
	HDC hBackBufferDC;
	RECT area = { 0,0,dfCLIENT_WIDTH,dfCLIENT_HEIGHT };

	Sprite* pSprite = nullptr;
	DWORD colorKey = 0x00FFFFFF; // �����
	int width = 0;
	int height = 0;
	int pitch = 0;
	int bitCount = 0;

	// �þ or �پ�� ������
	int clientWidth = dfCLIENT_WIDTH;
	int clientHeight = dfCLIENT_HEIGHT;

	// ī�޶� �׽�Ʈ��
	int x = 0;
	int y = 0;
};

