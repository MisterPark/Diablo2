#pragma once
#include "GameObject.h"
class UI : public GameObject
{
public:
	UI() { type = ObjectType::UI; }
	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void Show() {};
	virtual void Hide() {};
	GameObject* pParent = nullptr;
	Transform localPosition;
	RECT area;
	COLORREF color = RGB(255, 255, 255);
};

