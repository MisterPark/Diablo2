#include "pch.h"
#include "ObjectManager.h"
#include "Character.h"
#include "Player.h"
#include "UI.h"
#include "BackGround.h"
#include "Logo.h"
#include "Label.h"
#include "BackTile.h"
#include "Tile.h"
#include "Monster.h"
#include "Effect.h"

ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

ObjectManager::ObjectManager()
{
	player = Player::GetInstance();
	CollisionManager::RegisterObject(player);
	BackGround::GetInstance();
}

ObjectManager::~ObjectManager()
{
	Player::Release();
	player = nullptr;
	CollisionManager::DisregisterObject(player);
	BackGround::Release();
}

ObjectManager * ObjectManager::GetInstance()
{
	if (pObjectManager == nullptr)
	{
		pObjectManager = new ObjectManager;
	}
	return pObjectManager;
}

GameObject * ObjectManager::CreateObject(ObjectType _type)
{
	GameObject* pObj = nullptr;
	switch (_type)
	{
	case ObjectType::BACK_TILE:
		pObj = new BackTile;
		break;
	case ObjectType::TILE:
		pObj = new Tile;
		break;
	case ObjectType::MONSTER:
		pObj = new Monster;
		break;
	case ObjectType::PLAYER:
		return Player::GetInstance();
	case ObjectType::EFFECT:
		pObj = new Effect;
		break;
	case ObjectType::UI:
		pObj = new UI();
		break;
	case ObjectType::LOGO:
		pObj = new Logo();
		break;
	case ObjectType::LABEL:
		pObj = new Label;
		break;
	default:
		return nullptr;
	}

	pObj->type = _type;
	pObj->uid = ++lastUid;
	pObjectManager->objectTable[(int)_type].push_back(pObj);

	if (dynamic_cast<Character*>(pObj) != nullptr)
	{
		CollisionManager::RegisterObject(pObj);
	}

	return pObj;
}

bool ObjectManager::DeleteObject(GameObject * _target)
{
	auto& objList = pObjectManager->objectTable[(int)_target->type];
	
	auto target = find(objList.begin(), objList.end(), _target);
	if (target != objList.end())
	{
		_target->Die();
		return true;
	}
	return false;
}

void ObjectManager::DestroyAll()
{
	auto& objTable = pObjectManager->objectTable;
	for (auto&objList  : objTable)
	{
		for (auto& iter : objList)
		{
			iter->Die();
		}
	}
}

void ObjectManager::DestroyAll(ObjectType _type)
{
	auto& objList = pObjectManager->objectTable[(int)_type];
	for (auto iter : objList)
	{
		iter->Die();
	}
}


int ObjectManager::FindTopStickTileY(GameObject* _stickTile)
{
	if (_stickTile == nullptr) return 0;

	int minY = 999999;
	auto& tileList = pObjectManager->objectTable[(int)ObjectType::TILE];
	auto iter = tileList.begin();
	auto end = tileList.end();
	for (; iter != end; ++iter)
	{
		Tile* tile = (Tile*)(*iter);
		if ((tile->option & dfTILE_OPTION_STICK) == false) continue;
		if (_stickTile->position.x != tile->position.x) continue;
		minY = min(minY, tile->position.y);
	}

	return minY;
}

void ObjectManager::Release()
{
	delete pObjectManager;
	pObjectManager = nullptr;
}

void ObjectManager::Update()
{
	BackGround::GetInstance()->Update();
	Player::GetInstance()->Update();

	auto& objTable = pObjectManager->objectTable;
	for (auto& objList : objTable)
	{
		for (auto& iter : objList)
		{
			if (!iter->isEnable) continue;
			iter->Update();
		}
	}
	
}

void ObjectManager::LateUpdate()
{
	GameObject* target = nullptr;

	auto& objTable = pObjectManager->objectTable;
	for (auto& objList : objTable)
	{
			auto iter = objList.begin();
			auto end = objList.end();
			for (; iter != end;)
			{
				target = *iter;
				if (target->isDead)
				{
					iter = objList.erase(iter);

					if (dynamic_cast<Character*>(target) != nullptr)
					{
						CollisionManager::DisregisterObject(target);
					}

					delete target;
				}
				else
				{
					++iter;
				}
			}
	}

	
	
	
}

void ObjectManager::Render()
{
	BackGround::GetInstance()->Render();
	Player::GetInstance()->Render();

	auto& objTable = pObjectManager->objectTable;
	for (auto& objList : objTable)
	{
		for (auto& iter : objList)
		{
			if (!iter->isVisible)continue;
			iter->Render();
		}
	}

	// 디버그용
	TimeManager::RenderFPS();
	Player::RenderPlayerInfo();
}

bool ObjectManager::IsVisibleCollider()
{
	return pObjectManager->isVisibleCollider;
}

void ObjectManager::SetVisibleCollider(bool _isVisible)
{
	pObjectManager->isVisibleCollider = _isVisible;
}
