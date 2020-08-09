#include "pch.h"
#include "Character.h"
#include "Player.h"

void Character::Update()
{
	
}

void Character::Render()
{
}


bool Character::IsCollided(const GameObject* _target)
{
	const Character* target = dynamic_cast<const Character*>(_target);
	if (target == nullptr) return false;
	if (target->type == type) return false;

	RECT myBox = this->simpleCollider + this->position;
	RECT targetBox = target->simpleCollider + target->position;
	RECT outBox;

	if (!IntersectRect(&outBox, &myBox, &targetBox)) return false;


	return true;
}

void Character::SetColliderSize(LONG left, LONG top, LONG right, LONG bottom)
{
	simpleCollider.left = left;
	simpleCollider.top = top;
	simpleCollider.right = right;
	simpleCollider.bottom = bottom;
}

void Character::PushOut(Character* target,DWORD option)
{
	RECT targetRect = target->simpleCollider + target->position;
	RECT myRect = simpleCollider + position;

	RECT area;
	if (IntersectRect(&area, &targetRect, &myRect) == false )return;
	int dx = area.right - area.left;
	int dy = area.bottom - area.top;

	if (dx >= dy)
	{
		if (targetRect.top < myRect.top)
		{
			if (option & dfTILE_OPTION_COLLISION_TOP)
			{
				int distance = targetRect.bottom - myRect.top;

				if (distance > 0)
				{
					target->position.y -= distance;
					target->gravityCount = 0;
					target->jumpFlag = true;
					target->isFalldown = false;
				}

				Player* p = dynamic_cast<Player*>(target);
				if (p != nullptr)
				{
					p->stickFlag = false;
				}
			}
		}
		else if (targetRect.bottom > myRect.bottom)
		{
			if (option & dfTILE_OPTION_COLLISION_BOTTOM)
			{
				int distance = myRect.bottom - targetRect.top;

				if (distance > 0)
				{
					target->position.y += distance;
					target->jumpCount = 0;
				}
			}
		}
	}
	else
	{
		if (targetRect.left < myRect.left)
		{
			if (option & dfTILE_OPTION_COLLISION_LEFT)
			{
				int distance = targetRect.right - myRect.left;

				if (distance > 0)
				{
					target->position.x -= distance;
				}
			}
		}
		else if (targetRect.right > myRect.right)
		{
			if (option & dfTILE_OPTION_COLLISION_RIGHT)
			{
				int distance = myRect.right - targetRect.left;

				if (distance > 0)
				{
					target->position.x += distance + 1;
				}
			}
		}
	}
}
