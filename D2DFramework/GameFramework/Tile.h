#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

