#include "pch.h"
#include "Tile.h"

void Tile::Update()
{
	anim->SetSpriteKey(spriteKey);
	anim->Update();
}

void Tile::Render()
{
	D2DRenderManager::DrawTile(spriteKey, transform, offsetIndex.row, offsetIndex.col);
}
