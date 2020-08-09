#pragma once
#include "UI.h"
class Logo : public UI
{
public:
	Logo();
	virtual ~Logo();

	virtual void Update() override;
	virtual void Render() override;
};

