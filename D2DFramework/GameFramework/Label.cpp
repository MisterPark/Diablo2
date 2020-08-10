#include "pch.h"
#include "Label.h"

Label::Label()
{
	position = { 0.f,0.f ,0.f};
	wmemset(text, 0, 64);
	wmemset(font, 0, 16);
}

Label::~Label()
{
}

void Label::Update()
{

}

void Label::Render()
{
	RenderManager::DrawString(text, position.x, position.y, fontSize, color);
}

void Label::SetText(const WCHAR* _text)
{
	wcscpy_s(text, _text);
}
