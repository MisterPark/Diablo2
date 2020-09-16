#include "pch.h"
#include "LeatherCap.h"

LeatherCap::LeatherCap()
{
	anim->SetSpriteKey(SpriteType::ITEM_FLP_SST);
	invenSprite = SpriteType::ITEM_INV_SST;
	slotW = 1;
	slotH = 3;

	label->SetText(L"이상하네");
}

LeatherCap::~LeatherCap()
{
}
