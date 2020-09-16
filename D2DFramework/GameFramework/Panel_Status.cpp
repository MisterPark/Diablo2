#include "pch.h"
#include "Panel_Status.h"
#include "Label.h"
#include "Character.h"
#include "Button.h"

Panel_Status* pStatusPanel = nullptr;

Panel_Status::Panel_Status()
{
	anim->SetSpriteKey(SpriteType::UI_PANEL_STATUS);
	transform.position.x = 80;
	transform.position.y = 62;
	isVisible = false;

	// 버튼
	exitBtn = new Button();
	exitBtn->SetSpriteImage(SpriteType::UI_BTN_BUYSELL);
	exitBtn->spriteIndex = 10;
	exitBtn->transform.position = { 209,450,0 };
	exitBtn->Click = Exit;

	// 라벨 메모리 할당
	nick = 					 new Label;
	className = 			 new Label;
	nick->SetColor(Color(255, 255, 255, 255));
	nick->SetFont(L"돋움", 11, 0);
	className->SetColor(Color(255, 255, 255, 255));
	className->SetFont(L"돋움", 11, 0);
	
	int end = MaxOfEnum<StatType>();
	for (int i = 0; i < end; i++)
	{
		labels[i] = new Label;
		labels[i]->SetColor(Color(255, 255, 255, 255));
		labels[i]->SetFont(L"돋움", 11, 0);
	}
	// 라벨 세팅
	nick->transform.position = { 150,75,0 };
	className->transform.position = { 310,75,0 };
	labels[(int)StatType::LEVEL]->transform.position = { 110,110,0 };
	labels[(int)StatType::EXP]->transform.position = { 200,110,0 };
	labels[(int)StatType::MAX_EXP]->transform.position = { 330,110,0 };
	labels[(int)StatType::STRENGTH]->transform.position = { 170,150,0 };
	labels[(int)StatType::DEXTERITY]->transform.position = { 170,210,0 };
	labels[(int)StatType::VITALITY]->transform.position = { 170,295,0 };
	labels[(int)StatType::ENERGY]->transform.position = { 170,358,0 };
	labels[(int)StatType::STAT_POINT]->transform.position = { 170,420,0 };
	labels[(int)StatType::STEMINA]->transform.position = { 365,295,0 };
	labels[(int)StatType::MAX_STEMINA]->transform.position = { 325,295,0 };
	labels[(int)StatType::LIFE]->transform.position = { 365,320,0 };
	labels[(int)StatType::MAX_LIFE]->transform.position = { 325,320,0 };
	labels[(int)StatType::MANA]->transform.position = { 365,358,0 };
	labels[(int)StatType::MAX_MANA]->transform.position = { 325,358,0 };
	labels[(int)StatType::FIRE_RES]->transform.position = { 365,397,0 };
	labels[(int)StatType::COLD_RES]->transform.position = { 365,420,0 };
	labels[(int)StatType::LIGHT_RES]->transform.position = { 365,445,0 };
	labels[(int)StatType::POISON_RES]->transform.position = { 365,468,0 };

	for (int i = 0; i < end; i++)
	{
		tags[i] = new Label;
		tags[i]->SetColor(Color(255, 255, 255, 255));
		tags[i]->SetFont(L"돋움", 11, 0);
	}
	tags[(int)StatType::LEVEL]->transform.position = { 103,97,0 };
	tags[(int)StatType::EXP]->transform.position = { 190,97,0 };
	tags[(int)StatType::MAX_EXP]->transform.position = { 300,97,0 };
	tags[(int)StatType::STRENGTH]->transform.position = { 110,150,0 };
	tags[(int)StatType::DEXTERITY]->transform.position = { 110,210,0 };
	tags[(int)StatType::VITALITY]->transform.position = { 110,295,0 };
	tags[(int)StatType::ENERGY]->transform.position = { 110,358,0 };
	tags[(int)StatType::STAT_POINT]->transform.position = { 110,420,0 };
	tags[(int)StatType::STEMINA]->transform.position = { 260,295,0 };
	tags[(int)StatType::MAX_STEMINA]->transform.position = { 325,295,0 };
	tags[(int)StatType::LIFE]->transform.position = { 260,320,0 };
	tags[(int)StatType::MAX_LIFE]->transform.position = { 325,320,0 };
	tags[(int)StatType::MANA]->transform.position = { 260,358,0 };
	tags[(int)StatType::MAX_MANA]->transform.position = { 325,358,0 };
	tags[(int)StatType::FIRE_RES]->transform.position = { 275,397,0 };
	tags[(int)StatType::COLD_RES]->transform.position = { 275,420,0 };
	tags[(int)StatType::LIGHT_RES]->transform.position = { 275,445,0 };
	tags[(int)StatType::POISON_RES]->transform.position = { 275,468,0 };

	tags[(int)StatType::LEVEL]->SetText(L"레벨");
	tags[(int)StatType::EXP]->SetText(L"경험치");
	tags[(int)StatType::MAX_EXP]->SetText(L"남은 경험치");
	tags[(int)StatType::STRENGTH]->SetText(L"힘");
	tags[(int)StatType::DEXTERITY]->SetText(L"민첩성");
	tags[(int)StatType::VITALITY]->SetText(L"생명력");
	tags[(int)StatType::ENERGY]->SetText(L"에너지");
	tags[(int)StatType::STAT_POINT]->SetText(L"남은 능력치");
	tags[(int)StatType::STEMINA]->SetText(L"스테미나");
	//tags[(int)StatType::MAX_STEMINA]->SetText(L"힘");
	tags[(int)StatType::LIFE]->SetText(L"라이프");
	//tags[(int)StatType::MAX_LIFE]->SetText(L"힘");
	tags[(int)StatType::MANA]->SetText(L"마나");
	//tags[(int)StatType::MAX_MANA]->SetText(L"힘");
	tags[(int)StatType::FIRE_RES]->SetText(L"파이어 저항력");
	tags[(int)StatType::COLD_RES]->SetText(L"콜드 저항력");
	tags[(int)StatType::LIGHT_RES]->SetText(L"라이트닝 저항력");
	tags[(int)StatType::POISON_RES]->SetText(L"포이즌 저항력");
}

Panel_Status::~Panel_Status()
{
	delete exitBtn;

	delete nick;
	delete className;

	int end = MaxOfEnum<StatType>();
	for (int i = 0; i < end; i++)
	{
		delete labels[i];
	}

	for (int i = 0; i < end; i++)
	{
		tags[i] = new Label;
		tags[i]->SetColor(Color(255, 255, 255, 255));
		tags[i]->SetFont(L"돋움", 11, 0);
	}
}

Panel_Status* Panel_Status::GetInstance()
{
	if (pStatusPanel == nullptr)
	{
		pStatusPanel = new Panel_Status;
	}
	return pStatusPanel;
}

void Panel_Status::Destroy()
{
	delete pStatusPanel;
}

void Panel_Status::Update()
{
	if (InputManager::GetKeyDown('A'))
	{
		isVisible = !isVisible;
	}
	if (InputManager::GetKeyDown(VK_ESCAPE))
	{
		isVisible = false;
	}

	Character* c = Player::GetInstance()->pChar;
	if (c == nullptr) return;

	nick->SetText(c->nick);
	className->SetText(c->className);
	int end = MaxOfEnum<StatType>();
	for (int i = 0; i < end; i++)
	{
		labels[i]->SetText(c->stat[i]);
	}

	exitBtn->Update();
}

void Panel_Status::Render()
{
	if (isVisible == false)return;
	D2DRenderManager::DrawUI(SpriteType::UI_PANEL_800L, Vector3(0,-2,0), 0);
	D2DRenderManager::DrawUI(anim->GetSpriteKey(), transform.position, 0);

	Character* c = Player::GetInstance()->pChar;
	if (c == nullptr) return;

	nick->Render();
	className->Render();
	int end = MaxOfEnum<StatType>();
	for (int i = 0; i < end; i++)
	{
		if (i == (int)StatType::STAT_POINT && c->stat[i] == 0) continue;
		labels[i]->Render();
	}
	for (int i = 0; i < end; i++)
	{
		if (i == (int)StatType::STAT_POINT && c->stat[i] == 0) continue;
		tags[i]->Render();
	}

	exitBtn->Render();
}

void Panel_Status::OnClick()
{
}

void Panel_Status::OnLButtonDown()
{
}

void Panel_Status::OnLButtonUp()
{
}

void Panel_Status::OnHover()
{
}

void Panel_Status::OnLeave()
{
}

void Panel_Status::OnChangedText()
{
}

void Panel_Status::Exit()
{
	pStatusPanel->isVisible = false;
}
