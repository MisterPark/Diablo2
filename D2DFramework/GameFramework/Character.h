#pragma once
#include "GameObject.h"
class Character :
    public GameObject
{
    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
};

