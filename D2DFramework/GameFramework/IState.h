#pragma once

class GameObject;

class IState
{
public:
	IState();
	virtual ~IState();

	virtual void Update(GameObject* pObj) = 0;

};

