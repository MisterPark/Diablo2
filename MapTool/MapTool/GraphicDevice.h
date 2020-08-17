#pragma once
class GraphicDevice
{
private:
	GraphicDevice();
	~GraphicDevice();
public:
	static GraphicDevice* GetInstance();
	static void Release();

public:
	static HRESULT InitializeDevice();
	static void ReleaseDevice();

	static void RenderBegin();
	static void RenderEnd();


	static LPDIRECT3DDEVICE9 GetDevice();
	static LPD3DXSPRITE GetSprite();
	static LPD3DXFONT GetFont();

private:
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	LPDIRECT3D9 pSDK = nullptr;
	LPD3DXSPRITE pSprite = nullptr;
	LPD3DXFONT pFont = nullptr;
};

