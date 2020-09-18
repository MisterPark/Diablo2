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

    void Stop();
    void Attack();
    bool SkillCast();
    void SkillCast2();

    void CastFireBolt();
    void CastFireBall();
    void CastInfreno();
    void CastInfrenoOff();
    void CastBlaze();
    void BlazeUpdate();
    void CastFireWall();
    void FireWallUpdate();
    void CastMeteor();
    void CastHydra();


    list<TableIndex> pathList;
    CharacterState state = CharacterState::NU;

    Animation* currentAnim = nullptr;
    Animation anims[MaxOfEnum<CharacterState>()] = {};

    float attackTick = 0.f;
    float attackDelay = 0.5f;
    float skillTick = 0.f;
    float skillDelay = 0.5f;
    float infernoTick = 0.f;
    float infernoDelay = 0.1f;
    float blazeTick = 0.f;
    float blazeDelay = 0.1f;
    float blazeTick2 = 0.f;
    float blazeDuration = 5.f;
    float firewallTick = 0.f;
    float firewallTick2 = 0.f;
    float firewallDelay = 0.1f;
    float firewallDuration = 2.5f;
    Vector3 firewallPos;
    float firewallDir =  0.f;

    bool infernoFlag = false;
    bool blazeFlag = false;
    bool firewallFlag = false;

    // stat
    wstring nick;
    wstring className;

    int stat[MaxOfEnum<StatType>()] = {  };
};

