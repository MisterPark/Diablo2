#include "pch.h"
#include "Character.h"

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
	attackTick += TimeManager::DeltaTime();
	skillTick += TimeManager::DeltaTime();

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
	if (!currentAnim->IsLoop() && currentAnim->GetCurrentFrame() == currentAnim->GetLastFrame())
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

void Character::Attack()
{
	if (attackTick > attackDelay)
	{
		attackTick = 0.f;
		FaceTarget(InputManager::GetMousePosOnWorld());
		state = CharacterState::A1_STF;
	}
	
}

void Character::SkillCast()
{
	if (skillTick > skillDelay)
	{
		skillTick = 0.f;
		FaceTarget(InputManager::GetMousePosOnWorld());
		state = CharacterState::SC_STF;
	}
}
