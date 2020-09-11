#include "pch.h"
#include "TestScene.h"
#include "BackGround.h"


void TestScene::OnLoaded()
{
	SoundManager::GetInstance()->StopAll();
	
	SoundManager::GetInstance()->PlayBGM((TCHAR*)L"RogueCamp.mp3");
	SoundManager::GetInstance()->SetVolume(SoundChannel::BGM, 0.5f);
	TileManager::Load("Act1Tile1.dat");

	BackGround::SetSprite(SpriteType::BG_BLACK);

	Player::GetInstance();
	Player::SetCharacter(ObjectType::SORCERESS);
	Player::SetVisible(true);
	Player::SetEnable(true);
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
