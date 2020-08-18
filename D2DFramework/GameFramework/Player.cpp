#include "pch.h"
#include "Player.h"
#include "Effect.h"
#include "Monster.h"

Player* pPlayer = nullptr;

Player::Player()
{
	// 정보
	hp = 10;
	position = { 30.f,250.f,0.f };
	speed = 200.f;
	isVisible = true;
	isEnable = true;

	direction = Direction::RIGHT;
	// 애니메이션
	anim->SetFrameDelay(0.1f);
	anim->SetLoop(true);

	// 상태
	
}

Player::~Player()
{
}

Player* Player::GetInstance()
{
	if (pPlayer == nullptr)
	{
		pPlayer = new Player;
	}
	return pPlayer;
}

void Player::Release()
{
	delete pPlayer;
}

void Player::RenderPlayerInfo()
{
	if (!pPlayer->isVisible) return;

	WCHAR w0[32] = { 0, };
	WCHAR w1[32];
	WCHAR w2[32];
	WCHAR w3[32];
	WCHAR w4[32];
	WCHAR w5[32];
	WCHAR w6[32];
	WCHAR w7[32];
	switch (pPlayer->state)
	{
	case 1:
		wsprintf(w0, L"LG");
		break;
	case 2:
		wsprintf(w0, L"TR");
		break;
	case 3:
		wsprintf(w0, L"LA");
		break;
	case 4:
		wsprintf(w0, L"RA");
		break;
	case 5:
		wsprintf(w0, L"HD");
		break;
	case 6:
		wsprintf(w0, L"S1");
		break;
	case 7:
		wsprintf(w0, L"S2");
		break;
	}
	
	wsprintf(w1, L"LG : %d,%d", pPlayer->lgX, pPlayer->lgY);
	wsprintf(w2, L"TR : %d,%d", pPlayer->trX, pPlayer->trY);
	wsprintf(w3, L"LA : %d,%d", pPlayer->laX, pPlayer->laY);
	wsprintf(w4, L"RA : %d,%d", pPlayer->raX, pPlayer->raY);
	wsprintf(w5, L"HD : %d,%d", pPlayer->hdX, pPlayer->hdY);
	wsprintf(w6, L"S1 : %d,%d", pPlayer->s1X, pPlayer->s1Y);
	wsprintf(w7, L"S2 : %d,%d", pPlayer->s2X, pPlayer->s2Y);
	RenderManager::DrawString(w0, 500, 80, RGB(0, 255, 0));
	RenderManager::DrawString(w1, 500, 100, RGB(0, 255, 0));
	RenderManager::DrawString(w2, 500, 120, RGB(0, 255, 0));
	RenderManager::DrawString(w3, 500, 140, RGB(0, 255, 0));
	RenderManager::DrawString(w4, 500, 160, RGB(0, 255, 0));
	RenderManager::DrawString(w5, 500, 180, RGB(0, 255, 0));
	RenderManager::DrawString(w6, 500, 200, RGB(0, 255, 0));
	RenderManager::DrawString(w7, 500, 220, RGB(0, 255, 0));
}

void Player::Update()
{
	if (isEnable == false) return;

	if (InputManager::GetKeyDown('L'))
	{
		isDrawLine = !isDrawLine;
	}

	if (InputManager::GetKeyDown('1'))
	{
		state = 1;
	}
	if (InputManager::GetKeyDown('2'))
	{
		state = 2;
	}
	if (InputManager::GetKeyDown('3'))
	{
		state = 3;
	}
	if (InputManager::GetKeyDown('4'))
	{
		state = 4;
	}
	if (InputManager::GetKeyDown('5'))
	{
		state = 5;
	}
	if (InputManager::GetKeyDown('6'))
	{
		state = 6;
	}
	if (InputManager::GetKeyDown('7'))
	{
		state = 7;
	}

	if (InputManager::GetKeyDown(VK_UP))
	{
		switch (state)
		{
		case 1:
			lgY--;
			break;
		case 2:
			trY--;
			break;
		case 3:
			laY--;
			break;
		case 4:
			raY--;
			break;
		case 5:
			hdY--;
			break;
		case 6:
			s1Y--;
			break;
		case 7:
			s2Y--;
			break;
		}
	}
	if (InputManager::GetKeyDown(VK_DOWN))
	{
		switch (state)
		{
		case 1:
			lgY++;
			break;
		case 2:
			trY++;
			break;
		case 3:
			laY++;
			break;
		case 4:
			raY++;
			break;
		case 5:
			hdY++;
			break;
		case 6:
			s1Y++;
			break;
		case 7:
			s2Y++;
			break;
		}
	}
	if (InputManager::GetKeyDown(VK_LEFT))
	{
		switch (state)
		{
		case 1:
			lgX--;
			break;
		case 2:
			trX--;
			break;
		case 3:
			laX--;
			break;
		case 4:
			raX--;
			break;
		case 5:
			hdX--;
			break;
		case 6:
			s1X--;
			break;
		case 7:
			s2X--;
			break;
		}
	}
	if (InputManager::GetKeyDown(VK_RIGHT))
	{
		switch (state)
		{
		case 1:
			lgX++;
			break;
		case 2:
			trX++;
			break;
		case 3:
			laX++;
			break;
		case 4:
			raX++;
			break;
		case 5:
			hdX++;
			break;
		case 6:
			s1X++;
			break;
		case 7:
			s2X++;
			break;
		}
	}

	


	anim->Update();
}

void Player::Render()
{
	if (isVisible == false) return;

	Transform pos = GetPositionFromCamera();
	//RenderManager::DrawSprite(SpriteType::NORMAL, anim->GetCurrentSpriteIndex(), pos.x, pos.y);
	RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::LG, 100 - 14 + lgX, 100 + 3 + lgY);
	RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::TR, 100 - 7+trX, 100 - 36+trY);
	RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::LA, 100 + 2+laX, 100 - 26+laY);
	RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::RA, 100 - 14+raX, 100 - 29+raY);
	RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::HD, 100-13+hdX, 100-49+hdY);
	RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::S1, 100-9+s1X, 100-51+s1Y);
	RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::S2, 100-2+s2X, 100-49+s2Y);
	
	
	
	
	if (isDrawLine)
	{
		RenderManager::DrawLine(100, 0, 100, dfCLIENT_HEIGHT, RGB(255, 0, 0));
		RenderManager::DrawLine(0, 100, dfCLIENT_WIDTH, 100, RGB(255, 0, 0));
	}
	
	
	if (ObjectManager::IsVisibleCollider())
	{
		RenderManager::DrawSimpleCollider(GetCollisionArea(), RGB(0, 255, 0));
	}
	
}

void Player::OnCollision(GameObject* _other)
{
}

void Player::Die()
{
	isDead = true;
}
