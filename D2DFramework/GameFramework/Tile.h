#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:

	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;


	wstring spriteKey;
	TableIndex worldIndex;
	TableIndex offsetIndex;
};

