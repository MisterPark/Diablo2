#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:

	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;


	wstring spriteKey;
	TableIndex worldIndex;
	TableIndex offsetIndex;
};

