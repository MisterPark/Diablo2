#pragma once


class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();

public:
	static CollisionManager* GetInstance();
	static void Release();

	static void Update();
	static void UpdateGravity();
	static void RegisterObject(GameObject* _pObj);
	static void DisregisterObject(GameObject* _pObj);
	static bool FindObject(GameObject* _pObj);

	static bool IsCollided(GameObject* target, GameObject* other);
	
	vector<GameObject*> objectList;
};

