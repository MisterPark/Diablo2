#pragma once
#include "UI.h"


class IScene
{
public:
	virtual void OnLoaded() = 0;
	virtual void OnUnloaded() = 0;
	virtual void Update() = 0;
	virtual bool ShowBox(UI* ptr) { ptr->Die(); return false; };
	virtual bool HideBox() { return false; };
	virtual ~IScene() = default;
};

