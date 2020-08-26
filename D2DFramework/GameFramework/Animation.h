#pragma once

class GameObject;
class Texture;

class Animation
{
public:
	Animation();
	Animation(const wstring& _spriteKey, GameObject* _ref);
	~Animation();

	void Update();
	void Render();

	wstring GetSpriteKey();
	void SetSpriteKey(const wstring& _spriteKey);

	void SetReferenceObject(GameObject* _target);
	void SetLoop(bool _loop);
	void SetDelay(float _delay);

private:
	wstring spriteKey;
	GameObject* ref = nullptr;
	Texture* tex = nullptr;
	int currentFrame = 0;
	float tick = 0.f;
	float delay = 0.1f;
	bool isLoop = false;
};

