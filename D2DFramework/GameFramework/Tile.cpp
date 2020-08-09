#include "pch.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"

Tile::Tile()
{
	position = { 0,0 };
	simpleCollider = { 0,0,dfTILE_W,dfTILE_H };
}

Tile::~Tile()
{
}

void Tile::Update()
{
	if (option & dfTILE_OPTION_MOVE)
	{
		int destX = ePoint.x * dfTILE_W;
		int destY = ePoint.y * dfTILE_H;

	}
}

void Tile::Render()
{
	Transform pos = GetPositionFromCamera();
	RenderManager::DrawTile(SpriteType::NORMAL, tileset, offsetIndex, pos.x, pos.y);
	//RenderManager::DrawSprite(SpriteType::NORMAL, SpriteIndex::STAGE1_TILE_SET, position.x, position.y);

	if (ObjectManager::IsVisibleCollider())
	{
		RenderManager::DrawSimpleCollider(pos + simpleCollider, RGB(0, 255, 0));
	}
	
}

void Tile::OnCollision(GameObject* _other)
{

}
