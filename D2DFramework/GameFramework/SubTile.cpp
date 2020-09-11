#include "pch.h"
#include "SubTile.h"

SubTile::SubTile()
{
}


void SubTile::Update()
{
	anim->SetSpriteKey(spriteKey);
	anim->Update();
}

void SubTile::Render()
{
	D2DRenderManager::DrawTile(spriteKey, transform, offsetIndex.row, offsetIndex.col);
}
