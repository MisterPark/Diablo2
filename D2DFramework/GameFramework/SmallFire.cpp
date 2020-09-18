#include "pch.h"
#include "SmallFire.h"

SmallFire::SmallFire()
{
	anim->SetSpriteKey(SpriteType::SKILL_SMALLFIRE_S);
	anim->SetLoop(false);
	speed = 0.f;
}

SmallFire::~SmallFire()
{
}

void SmallFire::Update()
{
	SpriteType stype = anim->GetSpriteKey();
	int currFrame = anim->GetCurrentFrame();

	switch (stype)
	{
	case SpriteType::SKILL_SMALLFIRE_S:
		if (currFrame == anim->GetLastFrame())
		{
			anim->SetSpriteKey(SpriteType::SKILL_SMALLFIRE);
			anim->SetCurrentFrame(0);
			anim->SetLoop(true);
		}
		break;
	case SpriteType::SKILL_SMALLFIRE:
		lifeTick += TimeManager::DeltaTime();
		if (lifeTick > lifeTime)
		{
			anim->SetSpriteKey(SpriteType::SKILL_SMALLFIRE_E);
			anim->SetCurrentFrame(0);
			anim->SetLoop(false);
		}
		break;
	case SpriteType::SKILL_SMALLFIRE_E:
		if (currFrame == anim->GetLastFrame())
		{
			Die();
		}
		break;
	}



	anim->Update();
}

void SmallFire::Render()
{
	D2DRenderManager::DrawCharacter(anim->GetSpriteKey(), transform, 0, anim->GetCurrentFrame());
}
