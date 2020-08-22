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
	// ���������� ��ġ�� �ٷ� ��ü. 
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	// ��ġ�� ���� ���� ���� �� ��ġ�� ������ ��ü�� ������ com ��ü .
	LPDIRECT3D9 pSDK = nullptr;
	// com ��ü!- �׳� �ϳ� �ϳ� ��ǰó�� �����Ѵٶ� �����ϸ� �ǰڴ�. 

	LPD3DXSPRITE pSprite = nullptr;
	LPD3DXFONT	pFont = nullptr;
};

