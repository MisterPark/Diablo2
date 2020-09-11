#include "pch.h"
#include "Player.h"
#include "Sorceress.h"

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

}

void Player::Release()
{

}

Player* Player::GetInstance()
{
    if (pPlayer == nullptr)
    {
        pPlayer = new Player();
    }
    return pPlayer;
}

void Player::DestroyInstance()
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
	if (InputManager::GetKey(VK_LBUTTON))
	{
		//pPlayer->pChar->PathFInding(InputManager::GetMousePosOnWorld());
		pPlayer->pChar->pathList.clear();
		pPlayer->pChar->nextPos = TileManager::MouseToWallIndex();
		pPlayer->pChar->isMoving = true;
	}

	

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
