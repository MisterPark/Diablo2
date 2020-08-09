#pragma once
#include "GameObject.h"
class BackTile :
	public GameObject
{
public:
	BackTile();
	virtual ~BackTile();

	virtual void Update() override;
	virtual void Render() override;

	SpriteIndex tileset;
	int offsetIndex = 0;
};

