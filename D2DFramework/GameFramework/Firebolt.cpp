#include "pch.h"
#include "Firebolt.h"

Firebolt::Firebolt()
{
	anim->SetSpriteKey(SpriteType::SKILL_FIREBOLT);
	anim->SetLoop(true);
	speed = 500.f;
}

Firebolt::~Firebolt()
{
}

void Firebolt::Update()
{
	Missile::Update();

	if (lifeTick > lifeTime)
	{
		Die();
	}
}
