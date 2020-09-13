#pragma once
#include "GameObject.h"

enum class CharacterState
{
    NU,
    TN,
    RN,
    A1,
    A2,
    SC,
    GH,

    NU_STF,
    TN_STF,
    RN_STF,
    A1_STF,
    A2_STF,
    SC_STF,
    GH_STF,


    END
};

class Character : public GameObject
{
public:
	Character();
	virtual ~Character();
    // GameObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;

    void UpdateAnimation();

    void PathFInding(Vector3 _targetPos);

    void Attack();
    void UpdateAttack();
    void SkillCast();

    list<TableIndex> pathList;
    CharacterState state = CharacterState::NU;
    SpriteType sprites[MaxOfEnum<CharacterState>()];

    float attackTick = 0.f;
    float attackDelay = 1.0f;
};

