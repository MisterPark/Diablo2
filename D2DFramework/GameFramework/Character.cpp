#include "pch.h"
#include "Character.h"

Character::Character()
{
	anim->SetSpriteKey(SpriteType::SO_NU_HTH);
	anim->SetLoop(true);
}

Character::~Character()
{
}

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
	Vector3 dir = { float(pt.x) + Camera::GetX(),float(pt.y) + Camera::GetY(),0.f };
	dir -= transform.position;
	direction = atan2f(dir.y, dir.x);

	anim->Update();
}

void Character::Render()
{
	anim->Render();
}
