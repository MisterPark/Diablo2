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

    // ���� ���� false�� ���� (�ѹ��� ������)
    bool damageFlag = true;
};

