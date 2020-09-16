#include "pch.h"
#include "Player.h"
#include "Sorceress.h"
#include "Label.h"
#include "Panel_Status.h"
#include "Inventory.h"
#include "Cursor.h"

Player* pPlayer = nullptr;

Player::Player()
{
	Initialize();
}

Player::~Player()
{
	Release();
}

void Player::Initialize()
{
	label = new Label();

}

void Player::Release()
{
	delete label;
}

Player* Player::GetInstance()
{
    if (pPlayer == nullptr)
    {
        pPlayer = new Player();
    }
    return pPlayer;
}

void Player::Destroy()
{
    if (pPlayer)
    {
        delete pPlayer;
        pPlayer = nullptr;
    }
}

void Player::Update()
{
    if (pPlayer->isEnable == false) return;
	if (pPlayer->pChar == nullptr) return;

	

	if (InputManager::GetKey(VK_UP))
	{
		pPlayer->pChar->transform.position.y -= 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		pPlayer->pChar->transform.position.y += 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		pPlayer->pChar->transform.position.x -= 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		pPlayer->pChar->transform.position.x += 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetMouseLButton())
	{
		if (Cursor::IsOnUI() == false)
		{
			if (!Cursor::HasItem())
			{
				if (InputManager::GetKey(VK_SHIFT))
				{
					pPlayer->pChar->Attack();
				}
				else
				{
					//pPlayer->pChar->PathFInding(InputManager::GetMousePosOnWorld());
					pPlayer->pChar->pathList.clear();
					pPlayer->pChar->nextPos = TileManager::MouseToWallIndex();
					pPlayer->pChar->isMoving = true;
				}
				
			}
			else
			{
				Item* item = Cursor::DropItem();
				item->isVisible = true;
				item->isEnable = true;
				item->anim->SetCurrentFrame(0);
				item->transform.position = pPlayer->pChar->transform.position;
				
			}
			
		}
		
		
	}

	if (InputManager::GetMouseRButton())
	{
		if (InputManager::GetKey(VK_SHIFT))
		{
			pPlayer->pChar->SkillCast();
		}
	}

	

	

}


void Player::RenderDebug()
{
	D2DRenderManager::DrawRect(0, 0, 100, 100);
	if (pPlayer->pChar == nullptr) return;
	WCHAR wstr[64] = {};
	swprintf_s(wstr, L"%d,%d", InputManager::GetMousePosOnClient().x, InputManager::GetMousePosOnClient().y);
	pPlayer->label->SetText(wstr);
	pPlayer->label->SetColor(Color::Red());
	pPlayer->label->Render();
}


void Player::SetCharacter(ObjectType _type)
{
	if (pPlayer->pChar)
	{
		ObjectManager::DeleteObject(pPlayer->pChar);
	}
	
	GameObject* pObj = ObjectManager::CreateObject(_type);
	Character* pChar = dynamic_cast<Character*>(pObj);
	if (pChar == nullptr)
	{
		ObjectManager::DeleteObject(pObj);
		pPlayer->pChar = nullptr;
		return;
	}

	Camera::SetTarget(pChar);
	pPlayer->pChar = pChar;
	pChar->speed = 200.f;
}

void Player::SetPosition(Vector3 pos)
{
	if (pPlayer->pChar)
		pPlayer->pChar->transform.position = pos;
}

void Player::SetVisible(bool _val)
{
	pPlayer->isVisible = _val;
	if(pPlayer->pChar)
		pPlayer->pChar->isVisible = _val;
}

void Player::SetEnable(bool _val)
{
	pPlayer->isEnable = _val;
	if(pPlayer->pChar)
		pPlayer->pChar->isEnable = _val;
}
