#pragma once
#include "Transform.h"
#include "Animation.h"
#include "IState.h"

enum class ObjectType
{
	// 렌더링 순서 중요 X ( Y 정렬)
	NONE,
	SUB_TILE,
	SORCERESS,

	ITEM_SHORT_STAFF,
	ITEM_CAP,
	ITEM_QUILTED_ARMOR,
	ITEM_BOOTS,
	ITEM_BELT,

	EFFECT_FIRECAST,
	EFFECT_COLDCAST,
	EFFECT_LIGHTCAST,
	EFFECT_EXPLODE,
	EFFECT_METEOR_TARGET,

	SKILL_FIREBOLT,
	SKILL_FIREBALL,
	SKILL_INFERNO,
	SKILL_FIREWALL,
	SKILL_SMALL_FIRE,
	SKILL_METEOR,
	SKILL_HYDRA,

	SKILL_TELEPORT,
	
	UI_LOGO,
	BUTTON,
	LABEL,

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
	void RotateToMouse();
	Vector3 GetPositionFromCamera();

	void FaceTarget(Vector3 targetPos);
	void Run(Vector3 targetPos);
	// 길찾기용 이동
	void Run(TableIndex targetIndex);


public:
	// 위치 방향
	Transform transform;
	//radian
	float direction = 0.f;
	float speed = 100.f;
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

	// 길찾기 관련
	TableIndex nextPos;
	bool isMoving = false;


};