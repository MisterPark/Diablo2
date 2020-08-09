#pragma once
#include "UI.h"
class Label :
	public UI
{
public:
	Label();
	virtual ~Label();

	virtual void Update() override;
	virtual void Render() override;

	void SetText(const WCHAR* _text);

	WCHAR text[64];
	WCHAR font[16];
	int fontSize = 11;
	COLORREF color = RGB(254, 254, 254);
};

