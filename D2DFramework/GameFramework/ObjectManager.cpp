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
#include "UI_StatusBar.h"
#include "Panel_Status.h"
#include "Inventory.h"
#include "ShortStaff.h"
#include "Cursor.h"
#include "LeatherCap.h"

ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

ObjectManager::ObjectManager()
{
	Player::GetInstance();
	BackGround::GetInstance();
	UI_StatusBar::GetInstance();
	Panel_Status::GetInstance();
	Inventory::GetInstance();
	Cursor::GetInstance();
}

ObjectManager::~ObjectManager()
{
	Player::Destroy();
	BackGround::Destroy();
	UI_StatusBar::Destroy();
	Panel_Status::Destroy();
	Inventory::Destroy();
	Cursor::Destroy();
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

	case ObjectType::ITEM_SHORT_STAFF:
		pObj = new ShortStaff;
		break;
	case ObjectType::ITEM_CAP:
		pObj = new LeatherCap;
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
	UI_StatusBar::GetInstance()->Update();
	Inventory::GetInstance()->Update();
	Panel_Status::GetInstance()->Update();
	Cursor::GetInstance()->Update();

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
			if (dynamic_cast<UI*>(iter))continue; // UI제외
			if (!iter->isVisible)continue; 
			if (iter->transform.position.x < camPos.x - dfCLIENT_WIDTH / 2) continue;
			if (iter->transform.position.y < camPos.y - dfCLIENT_HEIGHT / 2) continue;
			if (iter->transform.position.x > camPos.x + dfCLIENT_WIDTH + dfCLIENT_WIDTH / 2) continue;
			if (iter->transform.position.y > camPos.y + dfCLIENT_HEIGHT + dfCLIENT_HEIGHT / 2) continue;
			

			pObjectManager->renderList.push_back(iter);
		}
	}

	// y값으로 정렬
	pObjectManager->renderList.sort(Compare);
	// 오브젝트 렌더링
	for (auto& obj : pObjectManager->renderList)
	{
		obj->Render();
	}
	// UI 렌더링

	Inventory::GetInstance()->Render();
	Panel_Status::GetInstance()->Render();
	UI_StatusBar::GetInstance()->Render();
	
	int begin = (int)ObjectType::UI_LOGO;
	int end = (int)ObjectType::END;
	
	for (int i = begin; i < end; i++)
	{
		auto& uiList = pObjectManager->objectTable[i];
		for (auto& iter : uiList)
		{
			iter->Render();
		}
	}
	

	Cursor::GetInstance()->Render();
	// 디버그용
	//TimeManager::RenderFPS();
}

void ObjectManager::PostRender()
{
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
