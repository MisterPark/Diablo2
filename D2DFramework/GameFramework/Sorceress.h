#pragma once
#include "Character.h"

class Sorceress :  public Character
{
public:
	Sorceress();
	virtual ~Sorceress();
	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

