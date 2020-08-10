#include "pch.h"
#include "BackTile.h"

BackTile::BackTile()
{
}

BackTile::~BackTile()
{
}

void BackTile::Update()
{
}

void BackTile::Render()
{
	D3DXVECTOR3 pos = GetPositionFromCamera();
	RenderManager::DrawTile(SpriteType::NORMAL, tileset, offsetIndex, pos.x, pos.y);
}
