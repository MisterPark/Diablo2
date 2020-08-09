#pragma once
class TimeManager
{
private:
	TimeManager();
	~TimeManager();

public:
	static TimeManager* GetInstance();
	static void Release();
	static void SetFrame(int _framePerSec);
	static bool SkipFrame();
	static float DeltaTime();
	static int GetFPS();
	static void RenderFPS();

private:
	// Frame Control
	__int64 frameCounter = 0; // ������ ī����(�ʴ� ����)
	__int64 targetFPS = 60; // ��ǥ ������
	__int64 fps = 0; // ������ FPS (��¿�)
	float deltaTime = 0.f; // ��ŸŸ��
	float targetFrameRate = 0; // ������ �� ��ǥ ��� �ð�
	__int64 oldTime = 0; // ������ ���������� �ð�
	float timeStack = 0;  // �����Ӵ� �ʰ�/�̸� �ð�(����)
	__int64 elapseSum = 0; // 1�� ������

	bool isUsedQueryPerformance = false;
	LARGE_INTEGER frequency;

};

