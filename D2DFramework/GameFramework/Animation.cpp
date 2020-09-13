#include "pch.h"
#include "Animation.h"
#include "Texture.h"


Animation::Animation()
{
}

Animation::Animation(SpriteType _spriteKey, GameObject * _ref)
{
	SetSpriteKey(_spriteKey);
	SetReferenceObject(_ref);
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (ref == nullptr)return;
	if (tex == nullptr)return;

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

void Animation::RenderCharacter()
{
	if (ref == nullptr)return;
	if (tex == nullptr)return;

	lastFrame = tex->colCount - 1;

	float angle = D3DXToDegree(ref->direction) + 630.f;
	angle += (360.f / 32.f);
	angle = fmodf(angle, 360.f);
	int directionIndex = angle / (360.f / 16.f);// -1;
	D2DRenderManager::DrawCharacter(spriteKey, ref->transform, directionIndex, currentFrame);
}

void Animation::RenderImage()
{
	if (tex == nullptr)return;
	
	D2DRenderManager::DrawImage(spriteKey, ref->transform);
}

void Animation::RenderSprite()
{
	if (tex == nullptr)return;

	lastFrame = tex->rowCount * tex->colCount - 1;

	D2DRenderManager::DrawSprite(spriteKey, ref->transform, currentFrame);

}

SpriteType Animation::GetSpriteKey()
{
	return spriteKey;
}

void Animation::SetSpriteKey(SpriteType _spriteKey)
{
	tex = D2DRenderManager::GetTexture(_spriteKey);
	this->spriteKey = _spriteKey;
}

void Animation::SetReferenceObject(GameObject * _target)
{
	ref = _target;
}

void Animation::SetLoop(bool _loop)
{
	this->isLoop = _loop;
}

void Animation::SetDelay(float _delay)
{
	this->delay = _delay;
}
