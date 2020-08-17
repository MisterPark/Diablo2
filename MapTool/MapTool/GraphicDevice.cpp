#include "pch.h"
#include "GraphicDevice.h"

GraphicDevice* pGraphicDevice = nullptr;

GraphicDevice::GraphicDevice()
{
}

GraphicDevice::~GraphicDevice()
{
    ReleaseDevice();
}

GraphicDevice* GraphicDevice::GetInstance()
{
    if (pGraphicDevice == nullptr)
    {
        pGraphicDevice = new GraphicDevice;
    }
    return pGraphicDevice;
}

void GraphicDevice::Release()
{
    delete pGraphicDevice;
}

HRESULT GraphicDevice::InitializeDevice()
{
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	//1.장치의 수준을 조사할 컴객체를 생성. 
	pGraphicDevice->pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(pGraphicDevice->pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		// 실패 했을때에 대한 메시지를 넣어줄 것. 
		AfxMessageBox(L"Get DeviceCaps Failed");

		return E_FAIL;
	}
	DWORD vp = 0;
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	//백 버퍼의 가로 세로 크기. 
	d3dpp.BackBufferWidth = dfCLIENT_WIDTH;
	d3dpp.BackBufferHeight = dfCLIENT_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;


	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hwnd;
	// 거짓이면 전체화면, 참이면  창모드을 사용하겠다. 
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//3. 조사하고 세팅한 데이터를 가지고 이제 장치를 제어할 컴객체를 생성하자!
	if (FAILED(pGraphicDevice->pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hwnd, vp, &d3dpp, &pGraphicDevice->pDevice)))
	{
		AfxMessageBox(L"Failed Creating Device");
		return E_FAIL;
	}
	if (FAILED(D3DXCreateSprite(pGraphicDevice->pDevice, &pGraphicDevice->pSprite)))
	{
		AfxMessageBox(L"Failed Creating Sprite");
		return E_FAIL;
	}
	D3DXFONT_DESCW tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Height = 20;
	tFontInfo.Width = 20;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"메이플스토리");
	if (FAILED(D3DXCreateFontIndirect(pGraphicDevice->pDevice, &tFontInfo, &pGraphicDevice->pFont)))
	{
		AfxMessageBox(L"폰트 생성 실패");
		return E_FAIL;
	}
	return S_OK;
}

void GraphicDevice::ReleaseDevice()
{
    if (pGraphicDevice->pFont)
    {
        delete pGraphicDevice->pFont;
        pGraphicDevice->pFont = nullptr;
    }
    if (pGraphicDevice->pSprite)
    {
        delete pGraphicDevice->pSprite;
        pGraphicDevice->pSprite = nullptr;
    }
    if (pGraphicDevice->pDevice)
    {
        delete pGraphicDevice->pDevice;
        pGraphicDevice->pDevice == nullptr;
    }
    if (pGraphicDevice->pSDK)
    {
        delete pGraphicDevice->pSDK;
        pGraphicDevice->pSDK = nullptr;
    }
}

void GraphicDevice::RenderBegin()
{
	pGraphicDevice->pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 255), 0.f, 0);
	pGraphicDevice->pDevice->BeginScene();
	pGraphicDevice->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void GraphicDevice::RenderEnd()
{
	pGraphicDevice->pSprite->End();
	pGraphicDevice->pDevice->EndScene();
	pGraphicDevice->pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

LPDIRECT3DDEVICE9 GraphicDevice::GetDevice()
{
	return pGraphicDevice->pDevice;
}

LPD3DXSPRITE GraphicDevice::GetSprite()
{
	return pGraphicDevice->pSprite;
}

LPD3DXFONT GraphicDevice::GetFont()
{
	return pGraphicDevice->pFont;
}
