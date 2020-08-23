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
}

void Character::Render()
{
	
	D2DRenderManager::DrawSprite(L"SOBW", transform, 1, 3);
}
