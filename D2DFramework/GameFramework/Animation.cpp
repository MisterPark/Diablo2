#include "pch.h"
#include "Animation.h"
#include "Texture.h"


Animation::Animation()
{
}

Animation::Animation(const wstring & _spriteKey, GameObject * _ref)
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

		if (currentFrame == tex->GetLastFrame()) // 마지막프레임이면
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

void Animation::Render()
{
	if (ref == nullptr)return;
	if (tex == nullptr)return;

	float angle = D3DXToDegree(ref->direction) + 630;
	angle = fmodf(angle, 360.f);
	int directionIndex = angle / (360 / 16) - 1;
	D2DRenderManager::DrawSprite(spriteKey, ref->transform, directionIndex, currentFrame);
}

wstring Animation::GetSpriteKey()
{
	return spriteKey;
}

void Animation::SetSpriteKey(const wstring& _spriteKey)
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
