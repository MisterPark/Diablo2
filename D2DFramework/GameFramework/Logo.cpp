#include "pch.h"
#include "Logo.h"

Logo::Logo()
{
	position.x = 0;
	position.y = 0;
}

Logo::~Logo()
{
}

void Logo::Update()
{
	anim->Update();
}

void Logo::Render()
{
	SpriteIndex index = anim->GetCurrentSpriteIndex();
	RenderManager::DrawSprite(SpriteType::NORMAL, index, position.x, position.y);
}
