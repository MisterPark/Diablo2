#pragma once
#include "Transform.h"
#include "Animation.h"
#include "IState.h"

enum class ObjectType
{
	// ������ ���� �߿�
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
	// ��ġ ����
	Transform transform;
	Direction direction = Direction::RIGHT;
	
	ObjectType type = ObjectType::NONE;
	
	int uid = 0;

	int hp = 5;

	bool isEnable = true;
	bool isVisible = true;
	bool isDead = false;
	bool isAlliance = true;

	

	//��������Ʈ ����
	Animation* anim = nullptr;

	// Ÿ����
	GameObject* target = nullptr;


};