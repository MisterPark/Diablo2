#include "pch.h"
#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	frameCount += TimeManager::DeltaTime();
	if (frameDelay <= frameCount)
	{
		frameCount = 0;
		// 스프라이트 인덱스 넘기기 ( 이넘클래스 개쓰래기)
		
		if (curIndex == endIndex)
		{
			if (isLoop)
			{
				curIndex = startIndex;
				return;
			}

			isEndFrame = true;
			return;
		}

		int index = (int)curIndex;
		index++;
		curIndex = (SpriteIndex)index;
	}
}

SpriteIndex Animation::GetCurrentSpriteIndex()
{
	return curIndex;
}

void Animation::SetAnimation(SpriteIndex _index)
{
	startIndex = _index;
	endIndex = _index;
	curIndex = _index;
}

void Animation::SetAnimation(SpriteIndex _start, SpriteIndex _end)
{
	startIndex = _start;
	endIndex = _end;
	if ((int)curIndex < (int)_start || (int)curIndex > (int)_end)
	{
 		curIndex = _start;
	}
}

void Animation::SetFrameDelay(float _second)
{
	frameCount = 0;
	frameDelay = _second;
}

void Animation::SetLoop(bool _isLoop)
{
	isLoop = _isLoop;
}

bool Animation::IsEndFrame()
{
	return isEndFrame;
}
