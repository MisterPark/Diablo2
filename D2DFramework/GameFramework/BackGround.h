#pragma once
#include "UI.h"
class BackGround : public UI
{
private:
	BackGround();
	virtual ~BackGround();

public:
	static BackGround* GetInstance();
	static void Release();
	static void SetAnimation(SpriteIndex _index);
	static void SetAnimation(SpriteIndex _startIndex, SpriteIndex _endIndex);
	static void SetStretch(bool _isFillClient);

	virtual void Update() override;
	virtual void Render() override;

private:
	bool isFillClient = true;
};

