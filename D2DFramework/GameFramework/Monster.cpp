#include "pch.h"
#include "Monster.h"
#include "Effect.h"

void Monster::Update()
{
}

void Monster::Render()
{
}

void Monster::OnCollision(GameObject* _other)
{
}

void Monster::Die()
{
	isDead = true;
	

}

void Monster::SetSpawnPosition(int x, int y)
{
	spawnPos.x = x;
	spawnPos.y = y;
	position.x = x;
	position.y = y;
	backAndForthPos.x = x+50;
	backAndForthPos.y = y;
}

void Monster::SetBackAndForth(int x, int y)
{
	backAndForthPos.x = x;
	backAndForthPos.y = y;
}

bool Monster::IsTargetClose()
{
	if (target == nullptr) return false;
	
	float dist = fabs(target->position.x - position.x);

	if (dist > attackRange) return false;

	return true;
}

void Monster::MoveLeft()
{
	position.x -= speed * TimeManager::DeltaTime();
	direction = Direction::LEFT;
}

void Monster::BackAndForth()
{
	int distance = 0;

	if (backAndForthFlag)
	{
		distance = spawnPos.x - position.x;
	}
	else
	{
		distance = backAndForthPos.x - position.x;
	}

	
	if (distance == 0) // 도착
	{
		backAndForthFlag = !backAndForthFlag;

	}
	else if (distance < 0) // 왼쪽으로 가야함
	{
		direction = Direction::LEFT;
		position.x -= speed * TimeManager::DeltaTime();
	}
	else // 오른쪽으로 가야함
	{
		direction = Direction::RIGHT;
		position.x += speed * TimeManager::DeltaTime();
	}
}
