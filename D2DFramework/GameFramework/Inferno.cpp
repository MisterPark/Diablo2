#include "pch.h"
#include "Inferno.h"

Inferno::Inferno()
{
	anim->SetSpriteKey(SpriteType::SKILL_INFERNO);
	anim->SetDelay(0.1f);
	anim->SetLoop(false);
	speed = 200.f;
}

Inferno::~Inferno()
{
}

void Inferno::Update()
{
	Missile::Update();

	if (upCount < upMax)
	{
		upCount += 1.0f;
		
	}
	transform.position.y -= upCount * TimeManager::DeltaTime();
	


	if (lifeTick > lifeTime)
	{
		Die();
	}
}

void Inferno::Render()
{
	D2DRenderManager::DrawCharacter(anim->GetSpriteKey(), transform, 0, anim->GetCurrentFrame());
}
