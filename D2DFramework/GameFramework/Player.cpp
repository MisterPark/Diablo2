#include "pch.h"
#include "Player.h"
#include "Sorceress.h"
#include "Label.h"

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

	barTrans.position.y = dfCLIENT_HEIGHT - 103;
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
	if (InputManager::GetMouseLButton())
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
	

	

}

void Player::RenderStatusBar()
{
	D2DRenderManager::DrawUI(SpriteType::UI_PANEL_STATUS_BAR, pPlayer->barTrans, 0);
	if (pPlayer->pChar == nullptr) return;

	
	
}

void Player::RenderDebug()
{
	if (pPlayer->pChar == nullptr) return;
	WCHAR wstr[64] = {};
	swprintf_s(wstr, L"%f", D3DXToDegree(pPlayer->pChar->direction));
	pPlayer->label->SetText(wstr);
	pPlayer->label->SetColor(Color(255, 255, 0, 0));
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
