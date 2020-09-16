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

void GameObject::RotateToMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	Vector3 dir = { float(pt.x) + Camera::GetX(),float(pt.y) + Camera::GetY(),0.f };
	dir -= transform.position;
	direction = atan2f(dir.y, dir.x);
}


Vector3 GameObject::GetPositionFromCamera()
{
	Vector3 pos = transform.position;
	pos.x -= Camera::GetX();
	pos.y -= Camera::GetY();
	return pos;
}

void GameObject::FaceTarget(Vector3 targetPos)
{
	Vector3 dir = targetPos;
	dir -= transform.position;
	direction = atan2f(dir.y, dir.x);
}

void GameObject::Run(Vector3 targetPos)
{
	Vector3 dir = targetPos;
	dir -= transform.position;
	transform.position.x += cosf(dir.x) * speed * TimeManager::DeltaTime();
	transform.position.y += sinf(dir.y) * speed * TimeManager::DeltaTime();
}

void GameObject::Run(TableIndex targetIndex)
{
	Vector3 dir = TileManager::WallIndexToWorldCenter(targetIndex);
	dir -= transform.position;
	direction = atan2f(dir.y, dir.x);
	transform.position.x += cosf(direction) * speed * TimeManager::DeltaTime();
	transform.position.y += sinf(direction) * speed * TimeManager::DeltaTime();
}
