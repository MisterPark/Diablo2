#pragma once
#include "GameObject.h"

enum class CharacterState
{
    NU,
    RN,

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

    list<TableIndex> pathList;
    CharacterState state = CharacterState::NU;
    SpriteType sprites[MaxOfEnum<CharacterState>()];
};

