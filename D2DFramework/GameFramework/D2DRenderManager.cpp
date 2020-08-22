#include "pch.h"
#include "D2DRenderManager.h"

D2DRenderManager* pD2DRenderManager = nullptr;

D2DRenderManager::D2DRenderManager()
{
}

D2DRenderManager::~D2DRenderManager()
{
	Release();
}

D2DRenderManager* D2DRenderManager::GetInstance()
{
	if (pD2DRenderManager == nullptr)
	{
		pD2DRenderManager = new D2DRenderManager();
		Initialize();
	}
	return pD2DRenderManager;
}

void D2DRenderManager::DestroyInstance()
{
	if (pD2DRenderManager)
	{
		delete pD2DRenderManager;
		pD2DRenderManager = nullptr;
	}
}

HRESULT D2DRenderManager::Initialize()
{
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	//1.��ġ�� ������ ������ �İ�ü�� ����. 
	pD2DRenderManager->pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(pD2DRenderManager->pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		// ���� �������� ���� �޽����� �־��� ��. 
		MessageBoxW(g_hwnd, L"Get DeviceCaps Failed", nullptr, MB_OK);

		return E_FAIL;
	}
	DWORD vp = 0;
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	//�� ������ ���� ���� ũ��. 
	d3dpp.BackBufferWidth = dfCLIENT_WIDTH;
	d3dpp.BackBufferHeight = dfCLIENT_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;


	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hwnd;
	// �����̸� ��üȭ��, ���̸�  â����� ����ϰڴ�. 
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//3. �����ϰ� ������ �����͸� ������ ���� ��ġ�� ������ �İ�ü�� ��������!
	if (FAILED(pD2DRenderManager->pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hwnd, vp, &d3dpp, &pD2DRenderManager->pDevice)))
	{
		MessageBoxW(g_hwnd, L"Failed Creating Device", nullptr, MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateSprite(pD2DRenderManager->pDevice, &pD2DRenderManager->pSprite)))
	{
		MessageBoxW(g_hwnd, L"Failed Creating Sprite", nullptr, MB_OK);
		return E_FAIL;
	}
	D3DXFONT_DESCW fontInfo;
	ZeroMemory(&fontInfo, sizeof(D3DXFONT_DESCW));
	fontInfo.Height = 20;
	fontInfo.Width = 20;
	fontInfo.Weight = FW_HEAVY;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"�����ý��丮");
	if (FAILED(D3DXCreateFontIndirect(pD2DRenderManager->pDevice, &fontInfo, &pD2DRenderManager->pFont)))
	{
		MessageBoxW(g_hwnd, L"��Ʈ ���� ����", nullptr, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void D2DRenderManager::Release()
{
	if (pD2DRenderManager->pFont)
	{
		pD2DRenderManager->pFont->Release();
	}
	if (pD2DRenderManager->pSprite)
	{
		pD2DRenderManager->pSprite->Release();
	}
	if (pD2DRenderManager->pDevice)
	{
		pD2DRenderManager->pDevice->Release();
	}
	if (pD2DRenderManager->pSDK)
	{
		pD2DRenderManager->pSDK->Release();
	}
}

void D2DRenderManager::Clear()
{
	pD2DRenderManager->pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 255), 0.f, 0);
	pD2DRenderManager->pDevice->BeginScene();
	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void D2DRenderManager::Present(HWND renderTarget)
{
	pD2DRenderManager->pSprite->End();
	pD2DRenderManager->pDevice->EndScene();
	pD2DRenderManager->pDevice->Present(nullptr, nullptr, renderTarget, nullptr);
}
