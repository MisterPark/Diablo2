#pragma once
#include "D2DRenderManager.h"
class GameObject;

class Animation
{
public:
	Animation();
	Animation(SpriteType _spriteKey);
	~Animation();

	void Update();
	void Initialize();

	SpriteType GetSpriteKey();
	int GetCurrentFrame();
	int GetLastFrame();
	bool IsLoop();

	void SetSpriteKey(SpriteType _spriteKey);
	void SetCurrentFrame(int _curr);
	void SetLastFrame(int _last);
	void SetLoop(bool _loop);
	void SetDelay(float _delay);

private:
	SpriteType spriteKey = SpriteType::NONE;
	
	int currentFrame = 0;
	int lastFrame = 0;
	float tick = 0.f;
	float delay = 0.1f;
	bool isLoop = false;
};

