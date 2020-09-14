#include "pch.h"
#include "Panel_Status.h"
#include "Label.h"
#include "Character.h"

Panel_Status* pStatusPanel = nullptr;

Panel_Status::Panel_Status()
{
	anim->SetSpriteKey(SpriteType::UI_PANEL_STATUS);
	transform.position.x = 80;
	transform.position.y = 62;
	isVisible = false;

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
	labels[(int)StatType::EXP]->transform.position = { 210,110,0 };
	labels[(int)StatType::MAX_EXP]->transform.position = { 310,110,0 };
	labels[(int)StatType::STRENGTH]->transform.position = { 110,160,0 };
	labels[(int)StatType::DEXTERITY]->transform.position = { 110,210,0 };
	labels[(int)StatType::VITALITY]->transform.position = { 110,260,0 };
	labels[(int)StatType::ENERGY]->transform.position = { 110,310,0 };
	labels[(int)StatType::STAT_POINT]->transform.position = { 110,110,0 };
	labels[(int)StatType::STEMINA]->transform.position = { 110,110,0 };
	labels[(int)StatType::MAX_STEMINA]->transform.position = { 110,110,0 };
	labels[(int)StatType::LIFE]->transform.position = { 110,110,0 };
	labels[(int)StatType::MAX_LIFE]->transform.position = { 110,110,0 };
	labels[(int)StatType::MANA]->transform.position = { 110,110,0 };
	labels[(int)StatType::MAX_MANA]->transform.position = { 110,110,0 };
	labels[(int)StatType::FIRE_RES]->transform.position = { 110,110,0 };
	labels[(int)StatType::COLD_RES]->transform.position = { 110,110,0 };
	labels[(int)StatType::LIGHT_RES]->transform.position = { 110,110,0 };
	labels[(int)StatType::POISON_RES]->transform.position = { 110,110,0 };
}

Panel_Status::~Panel_Status()
{
	delete nick;
	delete className;
	int end = MaxOfEnum<StatType>();
	for (int i = 0; i < end; i++)
	{
		delete labels[i];
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
}

void Panel_Status::Render()
{
	if (isVisible == false)return;
	D2DRenderManager::DrawUI(SpriteType::UI_PANEL_800L, Vector3(0,-2,0), 0);
	anim->RenderImage();

	nick->Render();
	className->Render();
	int end = MaxOfEnum<StatType>();
	for (int i = 0; i < end; i++)
	{
		labels[i]->Render();
	}
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
