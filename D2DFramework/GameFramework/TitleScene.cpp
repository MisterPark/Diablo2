#include "pch.h"
#include "TitleScene.h"
#include "BackGround.h"
#include "UI.h"
#include "Button.h"
#include "TestScene.h"

void TitleScene::OnLoaded()
{

	BackGround::SetSprite(SpriteType::BG_TITLE);
	Player::GetInstance();
	Player::SetVisible(false);
	Player::SetEnable(false);


	ObjectManager::CreateObject(ObjectType::UI_LOGO);
	Button* btn = (Button*)ObjectManager::CreateObject(ObjectType::BUTTON);
	btn->SetSpriteImage(SpriteType::UI_BTN_WIDE);

	int x = (dfCLIENT_WIDTH - btn->area.right) / 2;
	int y = (dfCLIENT_WIDTH - btn->area.right) / 2;
	btn->SetPosition(x, y);
	btn->SetText(L"�̱� �÷��̾�");
	btn->SetFont(L"����", 15, FW_BOLD);
	btn->Click = LoadSingleGameScene;

	btn = (Button*)ObjectManager::CreateObject(ObjectType::BUTTON);
	btn->SetSpriteImage(SpriteType::UI_BTN_HALFWIDE);
	btn->SetPosition(x, y + 43);
	btn->SetText(L"��Ʋ��");
	btn->SetFont(L"����", 15, FW_BOLD);

	btn = (Button*)ObjectManager::CreateObject(ObjectType::BUTTON);
	btn->SetSpriteImage(SpriteType::UI_BTN_NARROW);
	btn->SetPosition(x, y + 78);
	btn->SetText(L"GATEWAY ASIA");
	btn->SetFont(L"����", 11, FW_BOLD);

	btn = (Button*)ObjectManager::CreateObject(ObjectType::BUTTON);
	btn->SetSpriteImage(SpriteType::UI_BTN_WIDE);
	btn->SetPosition(x, y + 110);
	btn->SetText(L"�ٸ� ��Ƽ�÷��̾�");
	btn->SetFont(L"����", 15, FW_BOLD);

	btn = (Button*)ObjectManager::CreateObject(ObjectType::BUTTON);
	btn->SetSpriteImage(SpriteType::UI_BTN_WIDE);
	btn->SetPosition(x, dfCLIENT_HEIGHT - (btn->area.bottom*2));
	btn->SetText(L"��ƺ�� ll ����");
	btn->SetFont(L"����", 15, FW_BOLD);
}

void TitleScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TitleScene::Update()
{
}

void TitleScene::LoadSingleGameScene()
{
	SceneManager::LoadScene<TestScene>();
}
