#pragma once
#include "GameObject.h"
class Character : public GameObject
{
public:
	Character() = default;
	~Character() = default;

	virtual void Update() override;
	virtual void Render() override;

	RECT GetCollisionArea();
	bool IsCollided(GameObject* _target);
	void SetColliderSize(LONG left, LONG top, LONG right, LONG bottom);

	// 충돌 옵션임
	void PushOut(Character* target, DWORD option);

public:
	float speed = 0.f;
	RECT simpleCollider; // 객체를 감싸는 커다란 사각영역
	vector<RECT> colliders; // 실제 충돌영역
	// 중력
	bool useGravity = false;
	bool isFalldown = false;
	float gravityCount = 0;
	int jumpCount = 0;
	bool attackFlag = true;
	float attackDelay = 0.25f;
	float attackTick = 0.f;
};
