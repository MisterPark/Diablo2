#include "pch.h"
#include "Character.h"

void Character::Update()
{
	if (InputManager::GetKey(VK_UP))
	{
		transform.position.y -= 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		transform.position.y += 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		transform.position.x -= 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		transform.position.x += 100.f * TimeManager::DeltaTime();
	}

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	Vector3 dir = { float(pt.x),float(pt.y),0.f };
	dir -= transform.position;
	direction = atan2f(dir.y, dir.x);
}

void Character::Render()
{
	float angle = D3DXToDegree(direction) + 630;
	angle = fmodf(angle, 360.f);
	CHAR str[16] = { 0, };
	sprintf_s(str, "%f", angle);
	int directionIndex = angle / (360 / 16) - 1;
	D2DRenderManager::DrawString(str);
	D2DRenderManager::DrawSprite(L"SONUHTH", transform, directionIndex, 0);
}
