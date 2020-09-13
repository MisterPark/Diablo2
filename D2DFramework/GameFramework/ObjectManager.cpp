#include "pch.h"
#include "ObjectManager.h"
#include "Character.h"
#include "SubTile.h"
#include "Sorceress.h"
#include "Player.h"
#include "BackGround.h"
#include "UI_Logo.h"
#include "Button.h"
#include "Label.h"

ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

ObjectManager::ObjectManager()
{
	Player::GetInstance();
	BackGround::GetInstance();
}

ObjectManager::~ObjectManager()
{
	Player::DestroyInstance();
	BackGround::DestroyInstance();
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
	case ObjectType::SUB_TILE:
		pObj = new SubTile;
		break;
	case ObjectType::SORCERESS:
		pObj = new Sorceress();
		break;
	case ObjectType::UI_LOGO:
		pObj = new UI_Logo;
		break;
	case ObjectType::BUTTON:
		pObj = new Button();
		break;
	case ObjectType::LABEL:
		pObj = new Label();
		break;
	default:
		return nullptr;
	}

	pObj->type = _type;
	pObj->uid = ++lastUid;
	pObjectManager->objectTable[(int)_type].push_back(pObj);
	pObjectManager->renderList.push_back(pObj);
	//if (dynamic_cast<Character*>(pObj) != nullptr)
	//{
	//	CollisionManager::RegisterObject(pObj);
	//}

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

void ObjectManager::Release()
{
	delete pObjectManager;
	pObjectManager = nullptr;
}

void ObjectManager::Update()
{
	Player::Update();
	BackGround::GetInstance()->Update();

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

			/*		if (dynamic_cast<Character*>(target) != nullptr)
					{
						CollisionManager::DisregisterObject(target);
					}*/

					delete target;
				}
				else
				{
					++iter;
				}
			}
	}

	
	
	
}

void ObjectManager::PreRender()
{
	BackGround::GetInstance()->Render();
}

void ObjectManager::Render()
{
	pObjectManager->renderList.clear();

	Vector3 camPos = Camera::GetPosition();
	
	auto& objTable = pObjectManager->objectTable;
	for (auto& objList : objTable)
	{
		for (auto& iter : objList)
		{
			if (!iter->isVisible)continue;
			if (iter->transform.position.x < camPos.x - dfCLIENT_WIDTH/2) continue;
			if (iter->transform.position.y < camPos.y - dfCLIENT_HEIGHT/2) continue;
			if (iter->transform.position.x > camPos.x + dfCLIENT_WIDTH + dfCLIENT_WIDTH / 2) continue;
			if (iter->transform.position.y > camPos.y + dfCLIENT_HEIGHT + dfCLIENT_HEIGHT / 2) continue;

			pObjectManager->renderList.push_back(iter);
		}
	}

	pObjectManager->renderList.sort(Compare);

	

	for (auto& obj : pObjectManager->renderList)
	{
		obj->Render();
	}

	// 디버그용
	//TimeManager::RenderFPS();
}

void ObjectManager::PostRender()
{
	Player::RenderStatusBar();
	Player::RenderDebug();
}

bool ObjectManager::Compare(GameObject* a, GameObject* b)
{
	return a->transform.position.y < b->transform.position.y;
}

bool ObjectManager::IsVisibleCollider()
{
	return pObjectManager->isVisibleCollider;
}

void ObjectManager::SetVisibleCollider(bool _isVisible)
{
	pObjectManager->isVisibleCollider = _isVisible;
}
