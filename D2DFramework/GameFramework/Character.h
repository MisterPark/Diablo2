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
    void SkillCast();

    list<TableIndex> pathList;
    CharacterState state = CharacterState::NU;

    Animation* currentAnim = nullptr;
    Animation anims[MaxOfEnum<CharacterState>()] = {};

    float attackTick = 0.f;
    float attackDelay = 0.5f;
    float skillTick = 0.f;
    float skillDelay = 0.5f;

    // stat
    wstring nick;
    wstring className;

    int stat[MaxOfEnum<StatType>()] = {  };
};

