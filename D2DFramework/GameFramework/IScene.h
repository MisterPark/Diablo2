#pragma once
class IScene
{
public:
	virtual void OnLoaded() = 0;
	virtual void OnUnloaded() = 0;
	virtual void Update() = 0;
	virtual ~IScene() = default;
};

