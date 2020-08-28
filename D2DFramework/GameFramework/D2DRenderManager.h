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
	static Texture* GetTexture(const wstring& _key);

	static HRESULT LoadSprite(const wstring& filePath, const wstring& spriteKey, DWORD row, DWORD col);
	static void DrawSprite(const wstring& spriteKey, Transform transform, DWORD row = 0, DWORD col = 0);

	static void DrawString(const string& text);
	static void DrawString(const wstring& text);
	static void DrawString(const wstring& text, float x, float y, D3DXCOLOR color);

	static void DrawLine(float sx, float sy, float ex, float ey);
	static void DrawLine(float sx, float sy, float ex, float ey, D3DXCOLOR color);


private:
	// ���������� ��ġ�� �ٷ� ��ü. 
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	LPDIRECT3D9 pSDK = nullptr;
	LPD3DXSPRITE pSprite = nullptr;
	LPD3DXFONT	pFont = nullptr;
	LPD3DXLINE pLine = nullptr;

	map<wstring, Texture*> textureMap;
};

