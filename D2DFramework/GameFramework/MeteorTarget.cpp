#include "pch.h"
#include "MeteorTarget.h"

MeteorTarget::MeteorTarget()
{
	anim->SetSpriteKey(SpriteType::EFFECT_METEOR_TARGET);
	anim->SetLoop(true);
}

MeteorTarget::~MeteorTarget()
{
}

void MeteorTarget::Update()
{
	lifeTick += TimeManager::DeltaTime();
	if (lifeTick > lifeDuration)
	{
		Die();
	}
	anim->Update();
}
