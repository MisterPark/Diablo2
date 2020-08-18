#pragma once
#include "Character.h"


enum class Command
{
	NONE,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	SIT_DOWN,
	JUMP,
	ATTACK,
};

class Player : public Character
{
private:
	Player();
	virtual ~Player();

public:
	static Player* GetInstance();
	static void Release();
	static void RenderPlayerInfo();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(GameObject* _other);
	virtual void Die() override;


	Command command = Command::NONE;

	bool isDrawLine = false;
	int state = 1;
	int lgX = 0;
	int lgY = 0;
	int trX = 0;
	int trY = 0;
	int laX = 0;
	int laY = 0;
	int raX = 0;
	int raY = 0;
	int hdX = 0;
	int hdY = 0;
	int s1X = 0;
	int s1Y = 0;
	int s2X = 0;
	int s2Y = 0;
};

