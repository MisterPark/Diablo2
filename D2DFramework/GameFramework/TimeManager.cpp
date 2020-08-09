#include "pch.h"
#include "TimeManager.h"

TimeManager* pTimeManager = nullptr;

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{

}

TimeManager* TimeManager::GetInstance()
{
	if (pTimeManager == nullptr)
	{
		pTimeManager = new TimeManager();

		if (QueryPerformanceFrequency(&pTimeManager->frequency))
		{
			pTimeManager->isUsedQueryPerformance = true;
		}
	}
	return pTimeManager;
}

void TimeManager::Release()
{
	delete pTimeManager;
	pTimeManager = nullptr;
}

void TimeManager::SetFrame(int _framePerSec)
{
	if (_framePerSec < 0)return;
	pTimeManager->targetFPS = _framePerSec;
	pTimeManager->targetFrameRate = 1000.f / _framePerSec;
}

bool TimeManager::SkipFrame()
{
	LARGE_INTEGER time;
	__int64 curTime;
	__int64 elapse; // 1������ ����ð� (ms)

	QueryPerformanceCounter(&time); // ���� ����ð�
	curTime = time.QuadPart;


	if (pTimeManager->oldTime == 0)
	{
		pTimeManager->oldTime = curTime;
		return false;
	}

	// �����Ӵ� �ɸ��ð� (����ũ�� ����)
	elapse = (curTime - pTimeManager->oldTime) / 10000;

	pTimeManager->elapseSum += elapse;
	// �õ�Ÿ�� ����
	pTimeManager->oldTime = curTime;
	// ��ŸŸ�� ����
	pTimeManager->deltaTime = float(elapse) / 1000.f;

	// ������ ī��Ʈ
	pTimeManager->frameCounter++;

	if (pTimeManager->elapseSum >= 1000) // 1�� �����
	{
		pTimeManager->fps = pTimeManager->frameCounter; // ��¿� fps����
		pTimeManager->frameCounter = 0; // 
		pTimeManager->elapseSum = 0;
	}

	// �����Ӵ� �ʰ�/�̸� �ð� 
	pTimeManager->timeStack += elapse - pTimeManager->targetFrameRate;

	if (pTimeManager->timeStack >= pTimeManager->targetFrameRate) // ������
	{
		pTimeManager->timeStack -= pTimeManager->targetFrameRate;
		return true;

	}
	else if (pTimeManager->timeStack < pTimeManager->targetFrameRate) // ������
	{
		Sleep(abs(pTimeManager->timeStack));
	}


	return false;
}

float TimeManager::DeltaTime()
{
	return pTimeManager->deltaTime;
}

int TimeManager::GetFPS()
{
	return pTimeManager->fps;
}

void TimeManager::RenderFPS()
{
	WCHAR wstr[8];
	wsprintf(wstr, L"%ld", pTimeManager->fps);
	RenderManager::DrawString(wstr, 0, 0, RGB(255, 60, 255));
}
