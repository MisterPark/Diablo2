#include "pch.h"
#include "Character.h"

Character::Character()
{
	direction = 180.f;
}

Character::~Character()
{
}

void Character::Update()
{
	
	if (isMoving)
	{
		state = CharacterState::RN;
		Move(nextPos);

		Vector3 nPos = TileManager::WallIndexToWorldCenter(nextPos);
		float gapX = fabsf(nPos.x - transform.position.x);
		float gapY = fabsf(nPos.y - transform.position.y);
		if (gapX < 10.f && gapY <10.f)
		{
			state = CharacterState::NU;
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
	anim->Update();
}

void Character::Render()
{
	anim->RenderCharacter();
}

void Character::UpdateAnimation()
{
	anim->SetSpriteKey(sprites[(int)state]);
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
			TileManager::GetPath(i, &path.col, &path.row);
			pathList.push_back(path);
		}
	}
	else
	{

	}
}
