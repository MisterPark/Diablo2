#pragma once
#include "GameObject.h"
class Character :
    public GameObject
{
public:
	Character();
	virtual ~Character();
    // GameObject��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
};

