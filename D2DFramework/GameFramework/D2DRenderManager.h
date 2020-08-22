#pragma once
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

private:
	// 실질적으로 장치를 다룰 객체. 
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	// 장치의 지원 수준 조사 및 장치를 제어할 객체를 생성할 com 객체 .
	LPDIRECT3D9 pSDK = nullptr;
	// com 객체!- 그냥 하나 하나 부품처럼 생각한다라 생각하면 되겠다. 

	LPD3DXSPRITE pSprite = nullptr;
	LPD3DXFONT	pFont = nullptr;
};

