#pragma once
#include "Character.h"

#define dfTILE_OPTION_NONE				0x00000000
#define dfTILE_OPTION_COLLISION_TOP		0x00000001
#define dfTILE_OPTION_COLLISION_BOTTOM	0x00000002
#define dfTILE_OPTION_COLLISION_LEFT	0x00000004
#define dfTILE_OPTION_COLLISION_RIGHT	0x00000008
#define dfTILE_OPTION_STICK				0x00000010
#define dfTILE_OPTION_JUMP_DOWN			0x00000020
#define dfTILE_OPTION_FALL_DOWN			0x00000040
#define dfTILE_OPTION_DAMAGE			0x00000080
#define dfTILE_OPTION_MOVE				0x00000100
#define dfTILE_OPTION_DEATH				0x00000200



class Tile : public Character
{
public:
	Tile();
	virtual ~Tile();

	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(GameObject* _other);

	SpriteIndex tileset;
	int offsetIndex = 0;
	DWORD option = dfTILE_OPTION_NONE;
	Point sPoint;
	Point ePoint; // 인덱스라서 타일크기 곱해줘야함
};

