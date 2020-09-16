#include "pch.h"
#include "TestScene.h"
#include "BackGround.h"
#include "Label.h"
#include "UI_StatusBar.h"

void TestScene::OnLoaded()
{
	SoundManager::GetInstance()->StopAll();
	
	SoundManager::GetInstance()->PlayBGM((TCHAR*)L"RogueCamp.mp3");
	SoundManager::GetInstance()->SetVolume(SoundChannel::BGM, 0.5f);
	TileManager::Load("Act1Tile1.dat");

	BackGround::SetSprite(SpriteType::BG_BLACK);

	Player::GetInstance();
	Player::SetCharacter(ObjectType::SORCERESS);
	Player::SetPosition(Vector3(2880, 650, 0));
	Player::SetVisible(true);
	Player::SetEnable(true);

	GameObject* item = ObjectManager::CreateObject(ObjectType::ITEM_SHORT_STAFF);
	item->transform.position = { 2700,750,0 };
	item = ObjectManager::CreateObject(ObjectType::ITEM_CAP);
	item->transform.position = { 2800,750,0 };
	item = ObjectManager::CreateObject(ObjectType::ITEM_QUILTED_ARMOR);
	item->transform.position = { 2900,750,0 };

	UI_StatusBar::GetInstance()->isVisible = true;
	UI_StatusBar::GetInstance()->isEnable = true;
}

void TestScene::OnUnloaded()
{
	Player::SetVisible(false);
	Player::SetEnable(false);
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{
}
