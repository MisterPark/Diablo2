#pragma once
#include <list>
#include "GameObject.h"

using namespace std;

class Player;

class ObjectManager
{
private:
	ObjectManager();
	~ObjectManager();
public:
	static ObjectManager* GetInstance();
	static GameObject* CreateObject(ObjectType _type);
	static bool DeleteObject(GameObject* _target);
	static void DestroyAll();
	static void DestroyAll(ObjectType _type);


	static void Release();
	static void Update();
	static void LateUpdate();
	static void PreRender();
	static void Render();
	static void PostRender();

	static bool Compare(GameObject* a, GameObject* b);

	static bool IsVisibleCollider();
	static void SetVisibleCollider(bool _isVisible);

private:
	list<GameObject*>objectTable[MaxOfEnum<ObjectType>()];
	list<GameObject*> renderList;
	bool isVisibleCollider = false;
	Player* player = nullptr;
};