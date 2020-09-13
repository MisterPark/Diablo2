#pragma once
#include "Character.h"

class Label;

class Player
{
private:
	Player();
	~Player();

	void Initialize();
	void Release();
public:
	static Player* GetInstance();
	static void DestroyInstance();

	static void Update();
	static void RenderStatusBar();
	static void RenderDebug();

	static void SetCharacter(ObjectType _type);
	static void SetVisible(bool _val);
	static void SetEnable(bool _val);

//private:
	Transform barTrans;
	Character* pChar = nullptr;
	ObjectType type = ObjectType::NONE;
	bool isVisible = false;
	bool isEnable = false;

private:
	// µð¹ö±×
	Label* label = nullptr;
};

