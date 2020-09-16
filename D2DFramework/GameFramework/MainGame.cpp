#include "pch.h"
#include "MainGame.h"
#include "TestScene.h"
#include "TitleScene.h"
#include "IntroScene.h"

MainGame* pMainGame = nullptr;

MainGame::MainGame()
{
	// 시작은 창모드로
	width = dfCLIENT_WIDTH;
	height = dfCLIENT_HEIGHT;

	// 풀스크린 모드 세팅
	fullMode.dmSize = sizeof(DEVMODE);
	fullMode.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
	fullMode.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
	fullMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &windowMode);
	// 창모드 (윈도우 크기랑, 작업영역 크기 저장)
	RECT windowRect;
	GetWindowRect(g_hwnd, &windowRect);
	windowWidth = windowRect.right - windowRect.left;
	windowHeight = windowRect.bottom - windowRect.top;
	RECT clientRect;
	GetClientRect(g_hwnd, &clientRect);
	windowClientWidth = clientRect.right - clientRect.left;
	windowClientHeight = clientRect.bottom - clientRect.top;

}

MainGame::~MainGame()
{
}

MainGame * MainGame::GetInstance()
{
	if (pMainGame == nullptr)
	{
		pMainGame = new MainGame();
	}
	return pMainGame;
}

void MainGame::Initialize()
{
	
	TimeManager::GetInstance();
	TimeManager::SetFrame(dfFPS);
	D2DRenderManager::GetInstance();
	CollisionManager::GetInstance();
	InputManager::GetInstance();
	ObjectManager::GetInstance();
	//RenderManager::GetInstance();
	
	SceneManager::GetInstance();
	
	Camera::GetInstance();
	TileManager::GetInstance();
	FileManager::GetInstance();

	SoundManager::GetInstance()->Initialize();

	

	D2DRenderManager::LoadSprite(L"Sprites\\Tile\\Act1_Town_Floor.png", SpriteType::ACT1_TOWN_FLOOR, 37, 5);
	D2DRenderManager::LoadSprite(L"Sprites\\Tile\\Act1_Outdoor_Floor.png", SpriteType::ACT1_OUTDOOR_FLOOR, 25, 5);
	D2DRenderManager::LoadSprite(L"Sprites\\Tile\\Act1_Town_Fence.png", SpriteType::ACT1_TOWN_FENCE, 1, 31);

	D2DRenderManager::LoadSprite(L"Sprites\\ui\\background.bmp", SpriteType::BG_BLACK, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\trademarkscreen.png", SpriteType::BG_INTRO, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\gameselectscreen.png", SpriteType::BG_TITLE, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\charactercreationscreen.png", SpriteType::BG_CHAR_CREATION, 1, 1);

	D2DRenderManager::LoadSprite(L"Sprites\\ui\\cursor.png", SpriteType::UI_CURSOR, 1, 8);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\logo.png", SpriteType::UI_LOGO, 30, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\WideButton.png", SpriteType::UI_BTN_WIDE, 1, 2);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\mediumSelButton.png", SpriteType::UI_BTN_MEDIUM, 1, 2);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\HalfWideButton.png", SpriteType::UI_BTN_HALFWIDE, 1, 2);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\NarrowButton.png", SpriteType::UI_BTN_NARROW, 1, 2);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\buysell_button.png", SpriteType::UI_BTN_BUYSELL, 1, 18);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\buysell_tabs.png", SpriteType::UI_TAB_BUYSELL, 1, 8);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\textbox.png", SpriteType::UI_TEXTBOX, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\800BorderLeft.png", SpriteType::UI_PANEL_800L, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\800BorderRight.png", SpriteType::UI_PANEL_800R, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\status_panel.png", SpriteType::UI_PANEL_STATUS, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\inven_panel.png", SpriteType::UI_PANEL_INVEN, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\buysell_panel.png", SpriteType::UI_PANEL_BUYSELL, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\StatusBar.png", SpriteType::UI_PANEL_STATUS_BAR, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\HPBall.png", SpriteType::UI_HP_BALL, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\MPBall.png", SpriteType::UI_MP_BALL, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\RedRect.png", SpriteType::UI_RECT_RED, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\ui\\BlackRect.png", SpriteType::UI_RECT_BLACK_ALPHA, 1, 1);


	D2DRenderManager::LoadSprite(L"Sprites\\Item\\invsst.png", SpriteType::ITEM_INV_SST, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\flpsst.png", SpriteType::ITEM_FLP_SST, 1, 17);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\invcap.png", SpriteType::ITEM_INV_CAP, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\flpcap.png", SpriteType::ITEM_FLP_CAP, 1, 17);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\invqlt.png", SpriteType::ITEM_INV_QLT, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\flpqlt.png", SpriteType::ITEM_FLP_QLT, 1, 17);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\invlbl.png", SpriteType::ITEM_INV_LBL, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\flplbl.png", SpriteType::ITEM_FLP_LBL, 1, 17);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\invlbt.png", SpriteType::ITEM_INV_LBT, 1, 1);
	D2DRenderManager::LoadSprite(L"Sprites\\Item\\flplbt.png", SpriteType::ITEM_FLP_LBT, 1, 17);

	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SOBW.png", SpriteType::SO_BW, 5, 6);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SONUHTH.png", SpriteType::SO_NU_HTH, 16, 8);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SORNHTH.png", SpriteType::SO_RN_HTH, 16, 8);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SOTNSTF.png", SpriteType::SO_TN_STF, 16, 16);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SORNSTF.png", SpriteType::SO_RN_STF, 16, 8);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SOA1STF.png", SpriteType::SO_A1_STF, 16, 18);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SOA2STF.png", SpriteType::SO_A2_STF, 16, 18);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SOSCSTF.png", SpriteType::SO_SC_STF, 16, 14);
	D2DRenderManager::LoadSprite(L"Sprites\\character\\so\\SOGHSTF.png", SpriteType::SO_GH_STF, 16, 8);



	SceneManager::LoadScene<IntroScene>();
	//SceneManager::LoadScene<TestScene>();
}

void MainGame::Release()
{
	SceneManager::Release();
	TimeManager::Release();
	ObjectManager::Release();
	//RenderManager::Release();
	D2DRenderManager::DestroyInstance();
	InputManager::Release();
	CollisionManager::Release();
	Camera::Release();
	TileManager::Release();
	FileManager::Release();

	SoundManager::DestroyInstance();
}

void MainGame::Run()
{
	
	InputManager::Update();
	TileManager::Update();
	ObjectManager::Update();
	Camera::Update();
	CollisionManager::Update();
	ObjectManager::LateUpdate();
	
	if (!TimeManager::SkipFrame())
	{
		D2DRenderManager::Clear();
		//D2DRenderManager::GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

		ObjectManager::PreRender();
		TileManager::Render();
		ObjectManager::Render();
		ObjectManager::PostRender();
		//D2DRenderManager::GetSprite()->End();

		//D2DRenderManager::GetLine()->Begin();
		TileManager::RenderLine();
		//D2DRenderManager::GetLine()->End();

		
		D2DRenderManager::Present();
	}
	
	SceneManager::Update();
}

void MainGame::Pause()
{
	pMainGame->isPause = true;
}

void MainGame::Resume()
{
	pMainGame->isPause = false;
}

void MainGame::Shutdown()
{
	PostQuitMessage(0);
}

bool MainGame::IsFullScreen()
{
	return pMainGame->isFullScreen;
}

void MainGame::WindowMode()
{
	ChangeScreenMode(false);
}

void MainGame::FullScreen()
{
	ChangeScreenMode(true);
	
}

void MainGame::ChangeScreenMode(bool _isFullScreen)
{
	RECT rect;
	pMainGame->isFullScreen = _isFullScreen;
	if (_isFullScreen)
	{
		SetWindowLong(g_hwnd, GWL_STYLE, WS_POPUP);
		pMainGame->width = GetSystemMetrics(SM_CXSCREEN);
		pMainGame->height = GetSystemMetrics(SM_CYSCREEN);
		//RenderManager::SetClientSize(pMainGame->width, pMainGame->height);
		SetWindowPos(g_hwnd, 0, 0, 0, pMainGame->width, pMainGame->height, SWP_SHOWWINDOW);
		ChangeDisplaySettings(&pMainGame->fullMode, CDS_FULLSCREEN);
	}
	else {
		SetWindowLong(g_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetRect(&rect, 0, 0, dfCLIENT_WIDTH, dfCLIENT_HEIGHT);
		constexpr int WIDOW_STYLE = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
		AdjustWindowRect(&rect, WIDOW_STYLE, false);

		pMainGame->width = pMainGame->windowClientWidth;
		pMainGame->height = pMainGame->windowClientHeight;
		//RenderManager::SetClientSize(pMainGame->width, pMainGame->height);

		// 윈도우 크기 설정
		
		SetWindowPos(g_hwnd, 0, 0, 0, pMainGame->windowWidth, pMainGame->windowHeight, SWP_SHOWWINDOW);
		ChangeDisplaySettings(&pMainGame->fullMode, CDS_RESET);
	}
}

int MainGame::GetClientWidth()
{
	return pMainGame->width;
}

int MainGame::GetClientHeight()
{
	return pMainGame->height;
}
