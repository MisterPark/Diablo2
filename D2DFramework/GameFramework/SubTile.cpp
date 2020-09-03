#include "pch.h"
#include "SubTile.h"

void SubTile::Update()
{
	anim->SetSpriteKey(spriteKey);
	anim->Update();
}

void SubTile::Render()
{
	D2DRenderManager::DrawTile(spriteKey, transform, offsetIndex.row, offsetIndex.col);
}
