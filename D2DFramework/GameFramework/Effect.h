#pragma once
#include "Character.h"
class Effect :
    public Character
{
public:
    Effect();
    virtual ~Effect();

    virtual void Update() override;
    virtual void Render() override;
    virtual void OnCollision(GameObject* _other);

    // 딜이 들어가면 false로 변경 (한번만 때리기)
    bool damageFlag = true;
};

