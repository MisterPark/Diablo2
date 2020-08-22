#include "pch.h"
#include "Camera.h"
#include "GameObject.h"

Camera* pCamera = nullptr;

Camera::Camera()
{
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
		pCamera->transform.position.x -= 2;
	}
	if (InputManager::GetKey(VK_NUMPAD6))
	{
		pCamera->transform.position.x += 2;
	}
	if (InputManager::GetKey(VK_NUMPAD8))
	{
		pCamera->transform.position.y -= 2;
	}
	if (InputManager::GetKey(VK_NUMPAD5))
	{
		pCamera->transform.position.y += 2;
	}
	if (InputManager::GetKey(VK_NUMPAD7))
	{
		SetPosition(0, 0);
	}

	FollowTarget();
}

void Camera::SetPosition(int _x, int _y)
{
	pCamera->transform.position.x = _x;
	pCamera->transform.position.y = _y;
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
	return pCamera->transform.position.x;
}

int Camera::GetY()
{
	return pCamera->transform.position.y;
}

void Camera::FollowTarget()
{
	if (pCamera->target == nullptr)return;


	pCamera->transform.position.x = pCamera->target->transform.position.x - (dfCLIENT_WIDTH / 2);
	pCamera->transform.position.y = pCamera->target->transform.position.y - (dfCLIENT_HEIGHT / 2);

	if (pCamera->transform.position.x < pCamera->minPos.x)
	{
		pCamera->transform.position.x = pCamera->minPos.x;
	}
	else if (pCamera->transform.position.x > pCamera->maxPos.x)
	{
		pCamera->transform.position.x = pCamera->maxPos.x;
	}

	if (pCamera->transform.position.y < pCamera->minPos.y)
	{
		pCamera->transform.position.y = pCamera->minPos.y;
	}
	else if (pCamera->transform.position.y > pCamera->maxPos.y)
	{
		pCamera->transform.position.y = pCamera->maxPos.y;
	}
}
