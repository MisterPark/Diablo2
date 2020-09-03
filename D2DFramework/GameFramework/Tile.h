#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:

	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

public:
	SpriteType spriteKey;
	TableIndex worldIndex;
	TableIndex offsetIndex;
	int isMoveable = 1;
};

