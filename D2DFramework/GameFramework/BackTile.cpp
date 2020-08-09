#include "pch.h"
#include "BackTile.h"

BackTile::BackTile()
{
	position = { 0,0 };
}

BackTile::~BackTile()
{
}

void BackTile::Update()
{
}

void BackTile::Render()
{
	Transform pos = GetPositionFromCamera();
	RenderManager::DrawTile(SpriteType::NORMAL, tileset, offsetIndex, pos.x, pos.y);
}
