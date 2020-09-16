#include "pch.h"
#include "ShortStaff.h"


ShortStaff::ShortStaff()
{
	anim->SetSpriteKey(SpriteType::ITEM_FLP_SST);
	invenSprite = SpriteType::ITEM_INV_SST;
	slotW = 1;
	slotH = 3;

	label->SetText(L"ผ๔ฝบลยวม");
}

ShortStaff::~ShortStaff()
{
}

