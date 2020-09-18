#include "pch.h"
#include "Meteor.h"

Meteor::Meteor()
{
	anim->SetSpriteKey(SpriteType::SKILL_METEOR);
	anim->SetLoop(true);
	speed = 1000.f;
	direction = D3DXToRadian(70.f);
	lifeTime = 4.f;
	isVisible = false;
}

Meteor::~Meteor()
{
}

void Meteor::Update()
{
	lifeTick += TimeManager::DeltaTime();


	if (isVisible)
	{
		transform.position.x += cosf(direction) * speed * TimeManager::DeltaTime();
		transform.position.y += sinf(direction) * speed * 0.5f * TimeManager::DeltaTime();

		if (transform.position.y > targetPos.y)
		{
			for (int i = 0; i < 20; i++)
			{
				int rx = rand() % 16 - 8;
				int ry = rand() % 10 - 5;
				rx *= i;
				ry *= i;
				GameObject* fire = ObjectManager::CreateObject(ObjectType::SKILL_SMALL_FIRE);
				fire->transform.position.x = targetPos.x + rx;
				fire->transform.position.y = targetPos.y + ry;
			}
			Die();
		}

		anim->Update();
	}

	if (lifeTick > lifeTime)
	{
		isVisible = true;
	}
	
}

void Meteor::Render()
{
	D2DRenderManager::DrawCharacter(anim->GetSpriteKey(), transform, 0, anim->GetCurrentFrame());
}

void Meteor::SetMeteorTarget(Vector3 _pos)
{
	transform.position.x = _pos.x - (sinf(direction) * 250.f);
	transform.position.y = _pos.y -(cosf(direction) * 1000.f);

	targetPos = _pos;
}
