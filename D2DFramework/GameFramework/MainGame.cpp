#include "pch.h"
#include "MainGame.h"
#include "TestScene.h"

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

	CollisionManager::GetInstance();
	InputManager::GetInstance();
	ObjectManager::GetInstance();
	RenderManager::GetInstance();
	SceneManager::GetInstance();
	
	Camera::GetInstance();
	TileManager::GetInstance();
	FileManager::GetInstance();

	SoundManager::GetInstance()->Initialize();

	RenderManager::LoadSprite(SpriteIndex::BACKGROUND, "Sprites\\background.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::BACKGROUND_W, "Sprites\\background2.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::BACKGROUND_200, "Sprites\\200.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::HD, "Sprites\\character\\so\\HD\\000.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::S1, "Sprites\\character\\so\\S1\\000.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::S2, "Sprites\\character\\so\\S2\\000.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::TR, "Sprites\\character\\so\\TR\\000.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::LA, "Sprites\\character\\so\\LA\\000.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::RA, "Sprites\\character\\so\\RA\\000.bmp", 0, 0);
	RenderManager::LoadSprite(SpriteIndex::LG, "Sprites\\character\\so\\LG\\000.bmp", 0, 0);

	SceneManager::LoadScene<TestScene>();
}

void MainGame::Release()
{
	SceneManager::Release();
	TimeManager::Release();
	ObjectManager::Release();
	RenderManager::Release();
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
	if (pMainGame->isPause == false)
	{
		ObjectManager::Update();
	}
	Camera::Update();
	CollisionManager::Update();
	ObjectManager::LateUpdate();
	
	if (!TimeManager::SkipFrame())
	{
		RenderManager::Clear();
		ObjectManager::Render();
		TileManager::Render();
		//RenderManager::Present();
		RenderManager::Flip();
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
		RenderManager::SetClientSize(pMainGame->width, pMainGame->height);
		SetWindowPos(g_hwnd, 0, 0, 0, pMainGame->width, pMainGame->height, SWP_SHOWWINDOW);
		ChangeDisplaySettings(&pMainGame->fullMode, CDS_FULLSCREEN);
	}
	else {
		// ChangeDisplaySettings(NULL, 0);
		SetWindowLong(g_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetRect(&rect, 0, 0, dfCLIENT_WIDTH, dfCLIENT_HEIGHT);
		constexpr int WIDOW_STYLE = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
		AdjustWindowRect(&rect, WIDOW_STYLE, false);
		//AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		pMainGame->width = pMainGame->windowClientWidth;
		pMainGame->height = pMainGame->windowClientHeight;
		RenderManager::SetClientSize(pMainGame->width, pMainGame->height);

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
