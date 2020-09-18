#include "pch.h"
#include "FireWall.h"

FireWall::FireWall()
{
	anim->SetSpriteKey(SpriteType::SKILL_FIREWALL_S);
	anim->SetLoop(false);
	speed = 0.f;
	
}

FireWall::~FireWall()
{
}

void FireWall::Update()
{
	SpriteType stype = anim->GetSpriteKey();
	int currFrame = anim->GetCurrentFrame();

	switch (stype)
	{
	case SpriteType::SKILL_FIREWALL_S:
		if (currFrame == anim->GetLastFrame())
		{
			anim->SetSpriteKey(SpriteType::SKILL_FIREWALL);
			anim->SetCurrentFrame(0);
			anim->SetLoop(true);
		}
		break;
	case SpriteType::SKILL_FIREWALL:
		lifeTick += TimeManager::DeltaTime();
		if (lifeTick > lifeTime)
		{
			anim->SetSpriteKey(SpriteType::SKILL_FIREWALL_E);
			anim->SetCurrentFrame(0);
			anim->SetLoop(false);
		}
		break;
	case SpriteType::SKILL_FIREWALL_E:
		if (currFrame == anim->GetLastFrame())
		{
			Die();
		}
		break;
	}

	

	anim->Update();
}

void FireWall::Render()
{
	D2DRenderManager::DrawCharacter(anim->GetSpriteKey(), transform, 0, anim->GetCurrentFrame());
}
