#pragma once
#include "RenderManager.h"

class Animation
{
public:
	Animation();
	~Animation();

	void Update();

	SpriteIndex GetCurrentSpriteIndex();

	void SetAnimation(SpriteIndex _index);
	void SetAnimation(SpriteIndex _start, SpriteIndex _end);
	void SetFrameDelay(float _second);
	void SetLoop(bool _isLoop);
	bool IsEndFrame();

private:
	SpriteIndex startIndex = SpriteIndex::NONE;
	SpriteIndex endIndex = SpriteIndex::NONE;
	SpriteIndex curIndex = SpriteIndex::NONE;
	float frameDelay = 0;
	float frameCount = 0;
	bool isLoop = false;
	bool isEndFrame = false;
};

