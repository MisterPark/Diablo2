#include "pch.h"
#include "CollisionManager.h"

CollisionManager* pCollisionManager = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
	if (pCollisionManager == nullptr)
	{
		pCollisionManager = new CollisionManager;
	}

	return pCollisionManager;
}

void CollisionManager::Release()
{
	delete pCollisionManager;
}

void CollisionManager::Update()
{

	// Ãæµ¹
	for (auto src : pCollisionManager->objectList)
	{
		for (auto dest : pCollisionManager->objectList)
		{
			if (src == dest) continue;
			if (src->type == dest->type)continue;

			if (CollisionManager::IsCollided(src, dest))
			{
				src->OnCollision(dest);
			}
		}
	}

	

}

void CollisionManager::RegisterObject(GameObject* _pObj)
{
	if (FindObject(_pObj))
	{
		return;
	}

	pCollisionManager->objectList.push_back(_pObj);
}

void CollisionManager::DisregisterObject(GameObject* _pObj)
{
	//if (FindObject(_pObj))
	//{
	//	//pCollisionManager->objectList.remove(_pObj);
	//}
	if (_pObj == nullptr) return;

	auto iter = pCollisionManager->objectList.begin();
	auto end = pCollisionManager->objectList.end();

	for (; iter != end; ++iter)
	{
		if ((*iter) != _pObj) continue;

		pCollisionManager->objectList.erase(iter);
		return;
	}
}

bool CollisionManager::FindObject(GameObject* _pObj)
{
	if (_pObj == nullptr) return false;
	for (auto iter : pCollisionManager->objectList)
	{
		if (iter != _pObj) continue;

		return true;
	}
	return false;
}

bool CollisionManager::IsCollided(GameObject* _target, GameObject* _other)
{
	return false;
}
