#pragma once
#include "GameObject.h"
class Effect :
    public GameObject
{
public:
    Effect();
    virtual ~Effect();
    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
};

