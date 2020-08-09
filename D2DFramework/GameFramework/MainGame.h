#pragma once


class MainGame
{
private:
	MainGame();
	~MainGame();

public:

	static MainGame* GetInstance();
	static void Initialize();
	static void Release();
	static void Run();
	static void Pause();
	static void Resume();
	static void Shutdown();
	static bool IsFullScreen();
	static void WindowMode();
	static void FullScreen();
	static void ChangeScreenMode(bool _isFullScreen);

	static int GetClientWidth();
	static int GetClientHeight();

	bool isPause = false;
private:
	bool isShutdown = false;
	bool isFullScreen = false;
	
	int width = 0;
	int height = 0;
	DEVMODE windowMode;
	DEVMODE fullMode;
	// 윈도우 모드 떄의 크기 저장
	int windowWidth = 0;
	int windowHeight = 0;
	int windowClientWidth = 0;
	int windowClientHeight = 0;
};

