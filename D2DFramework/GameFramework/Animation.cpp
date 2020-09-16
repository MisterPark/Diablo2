#include "pch.h"
#include "Animation.h"
#include "Texture.h"


Animation::Animation()
{
}

Animation::Animation(SpriteType _spriteKey)
{
	SetSpriteKey(_spriteKey);
}

Animation::~Animation()
{
}

void Animation::Update()
{
	tick += TimeManager::DeltaTime();
	if (tick >= delay)
	{
		tick = 0.f;

		if (currentFrame >= lastFrame) // 마지막프레임이면
		{
			if (isLoop) // 루프면
			{
				currentFrame = 0;
			}

			return;
		}

		currentFrame++;
	}
}
void Animation::Initialize()
{
	currentFrame = 0;
}
//
//void Animation::RenderCharacter()
//{
//	if (ref == nullptr)return;
//	Texture* tex = D2DRenderManager::GetTexture(spriteKey);
//	if (tex == nullptr)return;
//
//	lastFrame = tex->colCount - 1;
//
//	float angle = D3DXToDegree(ref->direction) + 630.f;
//	angle += (360.f / 32.f);
//	angle = fmodf(angle, 360.f);
//	int directionIndex = angle / (360.f / 16.f);// -1;
//	D2DRenderManager::DrawCharacter(spriteKey, ref->transform, directionIndex, currentFrame);
//}
//
//void Animation::RenderImage()
//{
//	Texture* tex = D2DRenderManager::GetTexture(spriteKey);
//	if (tex == nullptr)return;
//	
//	D2DRenderManager::DrawImage(spriteKey, ref->transform);
//}
//
//void Animation::RenderSprite()
//{
//	Texture* tex = D2DRenderManager::GetTexture(spriteKey);
//	if (tex == nullptr)return;
//
//	lastFrame = tex->rowCount * tex->colCount - 1;
//
//	D2DRenderManager::DrawSprite(spriteKey, ref->transform, currentFrame);
//
//}

SpriteType Animation::GetSpriteKey()
{
	return spriteKey;
}

int Animation::GetCurrentFrame()
{
	return this->currentFrame;
}

int Animation::GetLastFrame()
{
	return this->lastFrame;
}

bool Animation::IsLoop()
{
	return this->isLoop;
}

void Animation::SetSpriteKey(SpriteType _spriteKey)
{
	this->spriteKey = _spriteKey;
	Texture* tex = D2DRenderManager::GetTexture(_spriteKey);
	if (tex == nullptr)return;

	lastFrame = tex->colCount - 1;
}

void Animation::SetCurrentFrame(int _curr)
{
	this->currentFrame = _curr;
}

void Animation::SetLastFrame(int _last)
{
	this->lastFrame = _last;
}

void Animation::SetLoop(bool _loop)
{
	this->isLoop = _loop;
}

void Animation::SetDelay(float _delay)
{
	this->delay = _delay;
}
