#pragma once

class Texture;

enum class SpriteType
{
	NONE,
	ACT1_TOWN_FLOOR,
	ACT1_OUTDOOR_FLOOR,
	ACT1_TOWN_FENCE,


	SO_BW,
	SO_NU_HTH,
};

class D2DRenderManager
{
private:
	D2DRenderManager();
	~D2DRenderManager();

public:
	static D2DRenderManager* GetInstance();
	static void DestroyInstance();

	static HRESULT Initialize();
	static void Release();

	static void Clear();
	static void SpriteBegin();
	static void SpriteEnd();
	static void LineBegin();
	static void LineEnd();
	static void Present(HWND renderTarget = nullptr);

	static LPDIRECT3DDEVICE9 GetDevice();
	static LPD3DXSPRITE GetSprite();
	static Texture* GetTexture(SpriteType _key);

	static HRESULT LoadSprite(const wstring& filePath, SpriteType spriteKey, DWORD row, DWORD col);
	static void DrawSprite(SpriteType spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);
	static void DrawTile(SpriteType spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);

	static void DrawString(const string& text);
	static void DrawString(const wstring& text);
	static void DrawString(const wstring& text, float x, float y, D3DXCOLOR color);

	static void DrawLine(float sx, float sy, float ex, float ey);
	static void DrawLine(float sx, float sy, float ex, float ey, D3DXCOLOR color);


private:
	// 실질적으로 장치를 다룰 객체. 
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	LPDIRECT3D9 pSDK = nullptr;
	LPD3DXSPRITE pSprite = nullptr;
	LPD3DXFONT	pFont = nullptr;
	LPD3DXLINE pLine = nullptr;

	map<SpriteType, Texture*> textureMap;
};

