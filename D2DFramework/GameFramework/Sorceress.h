#pragma once
#include "Character.h"

class Sorceress :  public Character
{
public:
	Sorceress();
	virtual ~Sorceress();
	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

