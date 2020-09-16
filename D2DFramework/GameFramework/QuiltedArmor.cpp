#include "pch.h"
#include "QuiltedArmor.h"

QuiltedArmor::QuiltedArmor()
{
	anim->SetSpriteKey(SpriteType::ITEM_FLP_QLT);
	invenSprite = SpriteType::ITEM_INV_QLT;
	slotW = 2;
	slotH = 3;

	label->SetText(L"퀼티드아머");
}

QuiltedArmor::~QuiltedArmor()
{
}
