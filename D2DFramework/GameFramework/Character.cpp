#include "pch.h"
#include "Character.h"
#include "Missile.h"
#include "Meteor.h"

Character::Character()
{
	direction = 180.f;
	currentAnim = &anims[(int)state];
	stat[(int)StatType::LIFE] = stat[(int)StatType::MAX_LIFE];
	stat[(int)StatType::MANA] = stat[(int)StatType::MAX_MANA];
}

Character::~Character()
{
}

void Character::Update()
{
	float delta = TimeManager::DeltaTime();
	attackTick += delta;
	skillTick += delta;
	infernoTick += delta;

	if (isMoving)
	{
		state = CharacterState::RN;
		Run(nextPos);

		Vector3 nPos = TileManager::WallIndexToWorldCenter(nextPos);
		float gapX = fabsf(nPos.x - transform.position.x);
		float gapY = fabsf(nPos.y - transform.position.y);
		if (gapX < 10.f && gapY <10.f)
		{
			state = CharacterState::TN;
			isMoving = false;
		}
	}
	else
	{
		if (pathList.empty() == false)
		{
			nextPos = pathList.front();
			pathList.pop_front();
			isMoving = true;
		}

	}
	
	FireWallUpdate();
	BlazeUpdate();
	UpdateAnimation();
	currentAnim->Update();
}

void Character::Render()
{
	float angle = D3DXToDegree(direction) + 630.f;
	angle += (360.f / 32.f);
	angle = fmodf(angle, 360.f);
	int directionIndex = angle / (360.f / 16.f);// -1;
	D2DRenderManager::DrawCharacter(currentAnim->GetSpriteKey(), transform, directionIndex, currentAnim->GetCurrentFrame());

}

void Character::UpdateAnimation()
{
	Animation* oldAnim = currentAnim;
	currentAnim = &anims[(int)state];
	if (oldAnim != currentAnim)
	{
		oldAnim->SetCurrentFrame(0);
	}
	if (!currentAnim->IsLoop() &&
		currentAnim->GetCurrentFrame() == currentAnim->GetLastFrame() &&
		infernoFlag == false)
	{
		state = CharacterState::TN;
		currentAnim->SetCurrentFrame(0);
		currentAnim = &anims[(int)state];
	}
	
}

void Character::PathFInding(Vector3 _targetPos)
{
	pathList.clear();

	Vector3 leftTop = transform.position;
	leftTop.x -= dfCLIENT_WIDTH / 2;
	leftTop.y -= dfCLIENT_HEIGHT / 2;
	TableIndex leftTopIndex = TileManager::PositionToWallIndex(leftTop);

	Vector3 rightBottom = transform.position;
	rightBottom.x += dfCLIENT_WIDTH / 2;
	rightBottom.y += dfCLIENT_HEIGHT / 2;
	TableIndex endPos = TileManager::PositionToWallIndex(rightBottom);

	TableIndex myPos = TileManager::PositionToWallIndex(transform.position);
	TableIndex targetPos = TileManager::PositionToWallIndex(_targetPos);

	TileManager::SetSearchSize(leftTopIndex.col, leftTopIndex.row, endPos.col, endPos.row);
	if (TileManager::PathFinding(myPos.col, myPos.row, targetPos.col, targetPos.row))
	{
		int count = TileManager::GetPathListCount();
		TableIndex path;
		for (int i = 0; i < count; i++)
		{
			if (i == 0)continue;
			TileManager::GetPath(i, &path.col, &path.row);
			pathList.push_back(path);
		}
	}
	else
	{

	}
}

void Character::Stop()
{
	pathList.clear();
	isMoving = false;

}

void Character::Attack()
{
	if (attackTick > attackDelay)
	{
		attackTick = 0.f;
		Stop();
		FaceTarget(InputManager::GetMousePosOnWorld());
		state = CharacterState::A2_STF;
	}
	
}

bool Character::SkillCast()
{
	if (skillTick > skillDelay)
	{
		skillTick = 0.f;
		Stop();
		FaceTarget(InputManager::GetMousePosOnWorld());
		state = CharacterState::SC_STF;



		return true;
	}
	return false;
}

void Character::SkillCast2()
{
	Stop();
	FaceTarget(InputManager::GetMousePosOnWorld());
	state = CharacterState::SC_STF;
}

void Character::CastFireBolt()
{
	if (SkillCast())
	{
		GameObject* bolt = ObjectManager::CreateObject(ObjectType::SKILL_FIREBOLT);
		bolt->transform.position = this->transform.position;
		bolt->transform.position.y -= 20;
		Vector3 dir = InputManager::GetMousePosOnWorld();
		dir -= bolt->transform.position;
		bolt->direction = atan2f(dir.y, dir.x);

		GameObject* eff = ObjectManager::CreateObject(ObjectType::EFFECT_FIRECAST);
		eff->transform.position = this->transform.position;
		eff->transform.position.y += 10;

	}
}

void Character::CastFireBall()
{
	if (SkillCast())
	{
		GameObject* bolt = ObjectManager::CreateObject(ObjectType::SKILL_FIREBALL);
		bolt->transform.position = this->transform.position;
		bolt->transform.position.y -= 20;
		Vector3 dir = InputManager::GetMousePosOnWorld();
		dir -= bolt->transform.position;
		bolt->direction = atan2f(dir.y, dir.x);

		GameObject* eff = ObjectManager::CreateObject(ObjectType::EFFECT_FIRECAST);
		eff->transform.position = this->transform.position;
		eff->transform.position.y += 10;

	}
}

void Character::CastInfreno()
{
	infernoFlag = true;
	SkillCast2();
	if (infernoTick > infernoDelay)
	{
		infernoTick = 0.f;
		GameObject* bolt = ObjectManager::CreateObject(ObjectType::SKILL_INFERNO);
		bolt->transform.position = this->transform.position;
		bolt->transform.position.y -= 20;
		Vector3 dir = InputManager::GetMousePosOnWorld();
		dir -= bolt->transform.position;
		bolt->direction = atan2f(dir.y, dir.x);
	}
	
	
}

void Character::CastInfrenoOff()
{
	infernoFlag = false;
}

void Character::CastBlaze()
{
	if (blazeFlag == false)
	{
		blazeFlag = true;

		GameObject* eff = ObjectManager::CreateObject(ObjectType::EFFECT_FIRECAST);
		eff->transform.position = this->transform.position;
		eff->transform.position.y += 10;
	}

}

void Character::BlazeUpdate()
{
	if (blazeFlag)
	{
		blazeTick += TimeManager::DeltaTime();
		blazeTick2 += TimeManager::DeltaTime();


		if (blazeTick2 > blazeDelay)
		{
			blazeTick2 = 0.f;
			GameObject* bolt = ObjectManager::CreateObject(ObjectType::SKILL_FIREWALL);
			bolt->transform.position = this->transform.position;

		}

	}

	if (blazeTick > blazeDuration)
	{
		blazeTick = 0.f;
		blazeFlag = false;
	}
}

void Character::CastFireWall()
{
	if (firewallFlag == false)
	{
		firewallFlag = true;

		
		GameObject* eff = ObjectManager::CreateObject(ObjectType::EFFECT_FIRECAST);
		eff->transform.position = this->transform.position;
		eff->transform.position.y += 10;
		firewallPos = InputManager::GetMousePosOnWorld();
		FaceTarget(firewallPos);
		Vector3 dir = firewallPos - transform.position;
		
		firewallDir = D3DXToDegree(atan2f(dir.y, dir.x));
		firewallDir += 90.f;
	}
}

void Character::FireWallUpdate()
{
	if (firewallFlag)
	{
		firewallTick += TimeManager::DeltaTime();
		firewallTick2 += TimeManager::DeltaTime();

		

		if (firewallTick2 > firewallDelay)
		{
			firewallTick2 = 0.f;
			Missile* bolt = (Missile*)ObjectManager::CreateObject(ObjectType::SKILL_FIREWALL);
			bolt->transform.position = firewallPos;
			bolt->transform.position.x += cosf(D3DXToRadian(firewallDir)) * firewallTick * 250.f;
			bolt->transform.position.y += sinf(D3DXToRadian(firewallDir)) * firewallTick * 250.f;
			bolt->lifeTime = 10.f;

			Missile* bolt2 = (Missile*)ObjectManager::CreateObject(ObjectType::SKILL_FIREWALL);
			bolt2->transform.position = firewallPos;
			bolt2->transform.position.x += cosf(D3DXToRadian(firewallDir + 180.f)) * firewallTick * 250.f;
			bolt2->transform.position.y += sinf(D3DXToRadian(firewallDir + 180.f)) * firewallTick * 250.f;
			bolt2->lifeTime = 10.f;
		}

	}

	if (firewallTick > firewallDuration)
	{
		firewallTick = 0.f;
		firewallFlag = false;
	}
}

void Character::CastMeteor()
{
	if (SkillCast())
	{
		Meteor* meteor = (Meteor*)ObjectManager::CreateObject(ObjectType::SKILL_METEOR);
		meteor->SetMeteorTarget(InputManager::GetMousePosOnWorld());

		GameObject* mt = ObjectManager::CreateObject(ObjectType::EFFECT_METEOR_TARGET);
		mt->transform.position = InputManager::GetMousePosOnWorld();
		
		GameObject* eff = ObjectManager::CreateObject(ObjectType::EFFECT_FIRECAST);
		eff->transform.position = this->transform.position;
		eff->transform.position.y += 10;

	}

}

void Character::CastHydra()
{
}
