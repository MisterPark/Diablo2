#pragma once

class Texture;

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
	static void Present(HWND renderTarget = nullptr);

	static LPDIRECT3DDEVICE9 GetDevice();
	static LPD3DXSPRITE GetSprite();

	static HRESULT LoadSprite(const wstring& filePath, const wstring& spriteKey, DWORD row, DWORD col);
	static void DrawSprite(const wstring& spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);

private:
	// 실질적으로 장치를 다룰 객체. 
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	LPDIRECT3D9 pSDK = nullptr;
	LPD3DXSPRITE pSprite = nullptr;
	LPD3DXFONT	pFont = nullptr;

	map<wstring, Texture*> textureMap;
};

