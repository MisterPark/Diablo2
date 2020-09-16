#include "pch.h"
#include "LeatherCap.h"

LeatherCap::LeatherCap()
{
	anim->SetSpriteKey(SpriteType::ITEM_FLP_CAP);
	invenSprite = SpriteType::ITEM_INV_CAP;
	slotW = 2;
	slotH = 2;

	label->SetText(L"ĸ");
}

LeatherCap::~LeatherCap()
{
}
