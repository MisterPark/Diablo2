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

	//1.장치의 수준을 조사할 컴객체를 생성. 
	pD2DRenderManager->pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(pD2DRenderManager->pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		// 실패 했을때에 대한 메시지를 넣어줄 것. 
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
	fontInfo.Width = 0;
	fontInfo.Weight = FW_HEAVY;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"돋움");
	if (FAILED(D3DXCreateFontIndirect(pD2DRenderManager->pDevice, &fontInfo, &pD2DRenderManager->pFont)))
	{
		MessageBoxW(g_hwnd, L"폰트 생성 실패", nullptr, MB_OK);
		return E_FAIL;
	}
	
	if (FAILED(D3DXCreateLine(pD2DRenderManager->pDevice, &pD2DRenderManager->pLine)))
	{
		MessageBoxW(g_hwnd, L"라인 생성 실패", nullptr, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void D2DRenderManager::Release()
{
	for (auto pair : pD2DRenderManager->textureMap)
	{
		delete pair.second;
	}
	pD2DRenderManager->textureMap.clear();

	if (pD2DRenderManager->pLine)
	{
		pD2DRenderManager->pLine->Release();
	}
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
}

void D2DRenderManager::Present(HWND renderTarget)
{
	pD2DRenderManager->pDevice->EndScene();
	pD2DRenderManager->pDevice->Present(nullptr, nullptr, renderTarget, nullptr);
}

LPDIRECT3DDEVICE9 D2DRenderManager::GetDevice()
{
	return pD2DRenderManager->pDevice;
}

LPD3DXSPRITE D2DRenderManager::GetSprite()
{
	return pD2DRenderManager->pSprite;
}

Texture * D2DRenderManager::GetTexture(SpriteType _key)
{
	auto find = pD2DRenderManager->textureMap.find(_key);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return nullptr;
	}

	return find->second;
}

LPD3DXLINE D2DRenderManager::GetLine()
{
	return pD2DRenderManager->pLine;
}

HRESULT D2DRenderManager::LoadSprite(const wstring& filePath, SpriteType spriteKey, DWORD row, DWORD col)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);

	if (find != pD2DRenderManager->textureMap.end()) return S_OK;

	Texture* tex = new Texture;

	if (FAILED(D3DXGetImageInfoFromFile(filePath.c_str(), &tex->imageInfo)))
	{
		MessageBox(g_hwnd, L"이미지 정보 불러오기 실패", nullptr, MB_OK);
		delete tex;
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileExW(
		pD2DRenderManager->pDevice,
		filePath.c_str(),
		tex->imageInfo.Width,
		tex->imageInfo.Height,
		tex->imageInfo.MipLevels,
		0,
		tex->imageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(255,0,0,0),
		nullptr,
		nullptr,
		&tex->pTexture)))
	{
		wstring errMsg = filePath + L"Create Texture Failed";
		MessageBox(g_hwnd, errMsg.c_str(), nullptr, MB_OK);
		delete tex;
		return E_FAIL;
	}

	tex->rowCount = row;
	tex->colCount = col;

	pD2DRenderManager->textureMap[spriteKey] = tex;

	return S_OK;
}

void D2DRenderManager::DrawSprite(SpriteType spriteKey, Transform transform, int index)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x - Camera::GetX(), transform.position.y - Camera::GetY(), 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawUI(SpriteType spriteKey, Transform transform, int index)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x, transform.position.y , 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawUI(SpriteType spriteKey, Vector3 pos, int index)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	Matrix world, trans;
	D3DXMatrixTranslation(&trans, pos.x, pos.y, 0.f);
	world = trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawCharacter(SpriteType spriteKey, Transform transform, DWORD row, DWORD col)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = int(tex->imageInfo.Width / tex->colCount);
	int h = int(tex->imageInfo.Height / tex->rowCount);
	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x - Camera::GetX(), transform.position.y - Camera::GetY(), 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(centerX, h, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();

}

void D2DRenderManager::DrawTile(SpriteType spriteKey, Transform transform, DWORD row, DWORD col)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = int(tex->imageInfo.Width / tex->colCount);
	int h = int(tex->imageInfo.Height / tex->rowCount);
	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x - Camera::GetX(), transform.position.y - Camera::GetY(), 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, h-dfTILE_H, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawSubTile(SpriteType spriteKey, Transform transform, DWORD row, DWORD col)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = int(tex->imageInfo.Width / tex->colCount);
	int h = int(tex->imageInfo.Height / tex->rowCount);
	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x - Camera::GetX(), transform.position.y - Camera::GetY(), 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(centerX, h - dfTILE_H_HALF, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawItem(SpriteType spriteKey, Vector3 pos, int index)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans;
	D3DXMatrixTranslation(&trans, pos.x-Camera::GetX(), pos.y-Camera::GetY(), 0.f);
	world = trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(centerX, h-20, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawImage(SpriteType spriteKey, Transform transform)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->imageInfo.Width;
	int h = tex->imageInfo.Height;

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x, transform.position.y, 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, nullptr, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawImage(SpriteType spriteKey, float x, float y, float verticalPer)
{
	auto find = pD2DRenderManager->textureMap.find(spriteKey);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->imageInfo.Width;
	int h = tex->imageInfo.Height;
	RECT rt;
	rt.left = 0;
	rt.top = h-h*verticalPer;
	rt.right = w;
	rt.bottom =  h;
	Matrix world, trans, rot, scale, parent;
	D3DXMatrixTranslation(&trans, x, y, 0.f);
	world = trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, &rt, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawString(const string & text)
{
	Matrix world;
	D3DXMatrixIdentity(&world);

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pFont->DrawTextA(pD2DRenderManager->pSprite, text.c_str(), lstrlenA(text.c_str()), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	pD2DRenderManager->pSprite->End();

}

void D2DRenderManager::DrawString(const wstring & text)
{
	Matrix world;
	D3DXMatrixIdentity(&world);
	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pFont->DrawTextW(pD2DRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawString(const wstring & text, float x, float y, D3DXCOLOR color)
{
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);
	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pFont->DrawTextW(pD2DRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, color);
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawString(const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect)
{
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);
	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pFont->DrawTextW(pD2DRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), outRect, 0, color);
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawString(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color)
{
	if (font == nullptr) return;
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);
	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	font->DrawTextW(pD2DRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, color);
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawString(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect)
{
	if (font == nullptr) return;
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);
	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	font->DrawTextW(pD2DRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), outRect, DT_CALCRECT, color);
	pD2DRenderManager->pSprite->End();

}

void D2DRenderManager::DrawLine(float sx, float sy, float ex, float ey)
{
	D3DXVECTOR2 point[2] = {};
	point[0].x = sx;
	point[0].y = sy;
	point[1].x = ex;
	point[1].y = ey;

	pD2DRenderManager->pLine->Begin();
	pD2DRenderManager->pLine->Draw(point, 2, D3DCOLOR_ARGB(255, 0, 0, 0));
	pD2DRenderManager->pLine->End();
}

void D2DRenderManager::DrawLine(float sx, float sy, float ex, float ey, D3DXCOLOR color)
{
	D3DXVECTOR2 point[2] = {};
	point[0].x = sx;
	point[0].y = sy;
	point[1].x = ex;
	point[1].y = ey;

	pD2DRenderManager->pLine->Begin();
	pD2DRenderManager->pLine->Draw(point, 2, color);
	pD2DRenderManager->pLine->End();
}

void D2DRenderManager::DrawRect(float sx, float sy, float ex, float ey)
{
	auto find = pD2DRenderManager->textureMap.find(SpriteType::UI_RECT_BLACK_ALPHA);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->imageInfo.Width;
	int h = tex->imageInfo.Height;

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, ex-sx, ey-sy, 0.f);
	D3DXMatrixTranslation(&trans, sx, sy, 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, nullptr, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}

void D2DRenderManager::DrawRectWorld(float sx, float sy, float ex, float ey)
{
	auto find = pD2DRenderManager->textureMap.find(SpriteType::UI_RECT_BLACK_ALPHA);
	if (find == pD2DRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->imageInfo.Width;
	int h = tex->imageInfo.Height;

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, ex - sx, ey - sy, 0.f);
	D3DXMatrixTranslation(&trans, sx - Camera::GetX(), sy - Camera::GetY(), 0.f);
	world = scale * trans;

	pD2DRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pD2DRenderManager->pSprite->SetTransform(&world);
	pD2DRenderManager->pSprite->Draw(tex->pTexture, nullptr, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pD2DRenderManager->pSprite->End();
}
