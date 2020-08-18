#pragma once
#include "Define.h"
#include <d3dx9.h>
#include "RenderManager.h"
#include "Animation.h"
#include "IState.h"

enum class ObjectType
{
	// ������ ���� �߿�
	NONE,
	BACK_TILE,
	TILE,
	MONSTER,
	PLAYER,
	EFFECT,

	UI,
	LOGO,
	SELECT_BOX,
	
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
	void SetAnimation(SpriteIndex _index);
	void SetAnimation(SpriteIndex _startIndex, SpriteIndex _endIndex);
	D3DXVECTOR3 GetPositionFromCamera();

	void FollowTarget();
	void FaceTarget();
	void TakeDamage(int _damage);
	bool KnockBack();

public:
	// ��ġ ����
	D3DXVECTOR3 position{ 0.f,0.f,0.f };
	D3DXVECTOR3 localPosition{ 0.f,0.f,0.f };
	Direction direction = Direction::RIGHT;
	int width = 0;
	int height = 0;
	
	ObjectType type = ObjectType::NONE;
	int hp = 5;
	int uid = 0;
	bool isEnable = true;
	bool isVisible = true;
	bool jumpFlag = false;
	bool isDead = false;
	bool isAlliance = true;
	bool isSitdown = false;
	//  ���ݹ޾��� �� �˹� ����
	Direction knockbackDirection = Direction::RIGHT;
	float knockbackDelay = 0.5f;
	float knockbackTick = 0.f;
	bool isAttacked = false;
	bool isImmortal = false;
	float immotalDelay = 0.5f;
	float immotalTick = 0.f;

	//��������Ʈ ����
	Animation* anim = nullptr;

	// Ÿ����
	GameObject* target = nullptr;


};