#include "pch.h"
#include "BackGround.h"

BackGround* pBG = nullptr;

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

BackGround* BackGround::GetInstance()
{
	if (pBG == nullptr)
	{
		pBG = new BackGround;
	}
	return pBG;
}

void BackGround::DestroyInstance()
{
	delete pBG;
}

void BackGround::SetSprite(SpriteType _type)
{
	pBG->anim->SetSpriteKey(_type);
}

void BackGround::Update()
{
	anim->Update();
}

void BackGround::Render()
{
	anim->RenderImage();
}
