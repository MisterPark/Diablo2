#pragma once
#include "Transform.h"
#include "Animation.h"
#include "IState.h"

enum class ObjectType
{
	// 렌더링 순서 중요
	NONE,
	CHARACTER,
	END
};


class GameObject
{
public:
	GameObject();
	virtual ~GameObject();


	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnCollision(GameObject* _other) {};
	virtual void Die();

	void SetPosition(float _x, float _y);
	void SetTarget(GameObject* _target);
	Vector3 GetPositionFromCamera();


public:
	// 위치 방향
	Transform transform;
	Direction direction = Direction::RIGHT;
	
	ObjectType type = ObjectType::NONE;
	
	int uid = 0;

	int hp = 5;

	bool isEnable = true;
	bool isVisible = true;
	bool isDead = false;
	bool isAlliance = true;

	

	//스프라이트 관련
	Animation* anim = nullptr;

	// 타겟팅
	GameObject* target = nullptr;


};