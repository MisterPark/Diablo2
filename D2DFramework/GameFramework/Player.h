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

	RECT idleCollider = { -10,-40,10,0 };
	RECT jumpCollider = { -10,-40,10,-20 };
	RECT sitCollider = { -10,-20,10,0 };
	RECT stickColliderL = { 10,-40,30,0 };
	RECT stickColliderR = { -30,-40,-10,0 };
	bool stickFlag = false;
	Direction stickDirection = Direction::LEFT;
	int stickMaxY = 0;
	int score = 0;
};

