#include "pch.h"
#include "Effect.h"
#include "Monster.h"

Effect::Effect()
{
	anim->SetFrameDelay(0.1f);
}

Effect::~Effect()
{
}

void Effect::Update()
{
	int x, y, w, h;
	RenderManager::GetSpriteSize(anim->GetCurrentSpriteIndex(),&w, &h);
	RenderManager::GetSpriteCenter(anim->GetCurrentSpriteIndex(), &x, &y);
	SetColliderSize(-x, -y, w-x, h-y);

	if (anim->IsEndFrame())
	{
		Die();
	}
	anim->Update();
}

void Effect::Render()
{
	Transform pos = GetPositionFromCamera();
	RenderManager::DrawSprite(SpriteType::NORMAL, anim->GetCurrentSpriteIndex(), pos.x, pos.y);

	if (ObjectManager::IsVisibleCollider())
	{
		RenderManager::DrawSimpleCollider(pos + simpleCollider, RGB(0, 255, 0));
	}
}

void Effect::OnCollision(GameObject* _other)
{
	if (dynamic_cast<Monster*>(_other) && isAlliance != _other->isAlliance)
	{
		damageFlag = false;
	}
}
