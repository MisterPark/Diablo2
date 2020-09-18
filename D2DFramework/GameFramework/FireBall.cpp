#include "pch.h"
#include "FireBall.h"

FireBall::FireBall()
{
	anim->SetSpriteKey(SpriteType::SKILL_FIREBALL);
	anim->SetLoop(true);
	speed = 500.f;
}

FireBall::~FireBall()
{
}

void FireBall::Update()
{
	Missile::Update();

	if (lifeTick > lifeTime)
	{
		Die();
	}
}
