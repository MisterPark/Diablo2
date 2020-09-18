#pragma once
#include "GameObject.h"
class Missile :
    public GameObject
{
public:
    Missile();
    virtual ~Missile();

    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;

    float lifeTick = 0.f;
    float lifeTime = 2.f;
};

