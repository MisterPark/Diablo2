#include "pch.h"
#include "Camera.h"
#include "GameObject.h"

Camera* pCamera = nullptr;

Camera::Camera()
{
	position = { 0,0 };
}

Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
	if (pCamera == nullptr)
	{
		pCamera = new Camera;
	}
	return pCamera;
}

void Camera::Release()
{
	delete pCamera;
}

void Camera::Update()
{
	if (InputManager::GetKey(VK_NUMPAD4))
	{
		pCamera->position.x -= 2;
	}
	if (InputManager::GetKey(VK_NUMPAD6))
	{
		pCamera->position.x += 2;
	}
	if (InputManager::GetKey(VK_NUMPAD8))
	{
		pCamera->position.y -= 2;
	}
	if (InputManager::GetKey(VK_NUMPAD5))
	{
		pCamera->position.y += 2;
	}
	if (InputManager::GetKey(VK_NUMPAD7))
	{
		SetPosition(0, 0);
	}

	FollowTarget();
}

void Camera::SetPosition(int _x, int _y)
{
	pCamera->position.x = _x;
	pCamera->position.y = _y;
}

void Camera::SetTarget(GameObject* _target)
{
	pCamera->target = _target;
}

void Camera::SetRangeX(int minX, int maxX)
{
	pCamera->minPos.x = minX;
	pCamera->maxPos.x = maxX;
}

void Camera::SetRangeY(int minY, int maxY)
{
	pCamera->minPos.y = minY;
	pCamera->maxPos.y = maxY;
}

int Camera::GetX()
{
	return pCamera->position.x;
}

int Camera::GetY()
{
	return pCamera->position.y;
}

void Camera::FollowTarget()
{
	if (pCamera->target == nullptr)return;


	pCamera->position.x = pCamera->target->position.x - (RenderManager::GetWidth() / 2);
	pCamera->position.y = pCamera->target->position.y - (RenderManager::GetHeight() / 2);

	if (pCamera->position.x < pCamera->minPos.x)
	{
		pCamera->position.x = pCamera->minPos.x;
	}
	else if (pCamera->position.x > pCamera->maxPos.x)
	{
		pCamera->position.x = pCamera->maxPos.x;
	}

	if (pCamera->position.y < pCamera->minPos.y)
	{
		pCamera->position.y = pCamera->minPos.y;
	}
	else if (pCamera->position.y > pCamera->maxPos.y)
	{
		pCamera->position.y = pCamera->maxPos.y;
	}
}
