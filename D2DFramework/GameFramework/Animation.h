#pragma once
#include "D2DRenderManager.h"
class GameObject;
class Texture;

class Animation
{
public:
	Animation();
	Animation(SpriteType _spriteKey, GameObject* _ref);
	~Animation();

	void Update();
	void RenderCharacter();
	void RenderImage();
	void RenderSprite();

	SpriteType GetSpriteKey();
	void SetSpriteKey(SpriteType _spriteKey);

	void SetReferenceObject(GameObject* _target);
	void SetLoop(bool _loop);
	void SetDelay(float _delay);

private:
	SpriteType spriteKey;
	GameObject* ref = nullptr;
	Texture* tex = nullptr;
	int currentFrame = 0;
	int lastFrame = 0;
	float tick = 0.f;
	float delay = 0.1f;
	bool isLoop = false;
};

