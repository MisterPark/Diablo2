#include "pch.h"
#include "GameObject.h"
#include "Animation.h"

GameObject::GameObject()
{
	anim = new Animation;
}

GameObject::~GameObject()
{
	delete anim;
}

void GameObject::Die()
{
	isDead = true;
}

void GameObject::SetPosition(float _x, float _y)
{
	transform.position.x = _x;
	transform.position.y = _y;
}

void GameObject::SetTarget(GameObject* _target)
{
	this->target = _target;
}


Vector3 GameObject::GetPositionFromCamera()
{
	Vector3 pos = transform.position;
	pos.x -= Camera::GetX();
	pos.y -= Camera::GetY();
	return pos;
}