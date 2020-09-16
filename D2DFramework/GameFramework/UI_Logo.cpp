#include "pch.h"
#include "UI_Logo.h"

UI_Logo::UI_Logo()
{
	anim->SetSpriteKey(SpriteType::UI_LOGO);
	anim->SetLoop(true);
	anim->SetDelay(0.03f);
	anim->SetLastFrame(29);

	transform.position.x = dfCLIENT_WIDTH / 2;
	transform.position.y = 90;
}

UI_Logo::~UI_Logo()
{
}

void UI_Logo::Update()
{
	anim->Update();
}

void UI_Logo::Render()
{
	D2DRenderManager::DrawSprite(anim->GetSpriteKey(), transform, anim->GetCurrentFrame());
}
