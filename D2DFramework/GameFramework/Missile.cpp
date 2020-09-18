#include "pch.h"
#include "Missile.h"

Missile::Missile()
{
	anim->SetDelay(0.05f);
	anim->SetLoop(true);
	isVisible = true;
}

Missile::~Missile()
{
}

void Missile::Update()
{
	lifeTick += TimeManager::DeltaTime();

	transform.position.x += cosf(direction) * speed * TimeManager::DeltaTime();
	transform.position.y += sinf(direction) * speed *0.5f* TimeManager::DeltaTime();
	anim->Update();

}

void Missile::Render()
{
	float angle = D3DXToDegree(direction) + 630.f;
	angle += (360.f / 32.f);
	angle = fmodf(angle, 360.f);
	int directionIndex = angle / (360.f / 16.f);// -1;
	D2DRenderManager::DrawCharacter(anim->GetSpriteKey(), transform, directionIndex, anim->GetCurrentFrame());

}
