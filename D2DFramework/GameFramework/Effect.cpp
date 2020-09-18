#include "pch.h"
#include "Effect.h"

Effect::Effect()
{
	anim->SetDelay(0.05f);
}

Effect::~Effect()
{
}

void Effect::Update()
{
	if (anim->GetCurrentFrame() == anim->GetLastFrame())
	{
		Die();
	}
	anim->Update();
}

void Effect::Render()
{
	D2DRenderManager::DrawCharacter(anim->GetSpriteKey(), transform, 0, anim->GetCurrentFrame());
}
