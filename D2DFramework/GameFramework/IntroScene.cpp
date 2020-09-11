#include "pch.h"
#include "IntroScene.h"
#include "BackGround.h"
#include "TitleScene.h"

void IntroScene::OnLoaded()
{
	
	SoundManager::GetInstance()->PlayBGM((TCHAR*)L"title.mp3");

	BackGround::SetSprite(SpriteType::BG_INTRO);
	Player::GetInstance();
	Player::SetVisible(false);
	Player::SetEnable(false);

	ObjectManager::CreateObject(ObjectType::UI_LOGO);
}

void IntroScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void IntroScene::Update()
{
	tick += TimeManager::DeltaTime();
	if (tick > delay)
	{
		SceneManager::LoadScene<TitleScene>();
	}

	if (InputManager::GetMouseLButtonDown())
	{
		SceneManager::LoadScene<TitleScene>();
	}
}
