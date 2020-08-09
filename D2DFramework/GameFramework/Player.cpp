#include "pch.h"
#include "Player.h"
#include "Effect.h"
#include "Monster.h"

Player* pPlayer = nullptr;

Player::Player()
{
	// ����
	hp = 10;
	position = { 30,250 };
	speed = 200.f;
	isVisible = false;
	isEnable = false;

	simpleCollider = idleCollider;
	direction = Direction::RIGHT;
	// �ִϸ��̼�
	anim->SetFrameDelay(0.1f);
	anim->SetLoop(true);

	// ����
	
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
}

void Player::Update()
{
	if (isEnable == false) return;

	anim->Update();
}

void Player::Render()
{
	if (isVisible == false) return;

	Transform pos = GetPositionFromCamera();
	RenderManager::DrawSprite(SpriteType::NORMAL, anim->GetCurrentSpriteIndex(), pos.x, pos.y);
	
	if (ObjectManager::IsVisibleCollider())
	{
		RenderManager::DrawSimpleCollider(pos + simpleCollider, RGB(0, 255, 0));
	}
	
}

void Player::OnCollision(GameObject* _other)
{
}

void Player::Die()
{
	isDead = true;
}
