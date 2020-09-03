#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:

	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

public:
	SpriteType spriteKey;
	TableIndex worldIndex;
	TableIndex offsetIndex;
	int isMoveable = 1;
};

