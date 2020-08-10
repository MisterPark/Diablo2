#pragma once

class GameObject;

class Camera
{
private:
	Camera();
	~Camera();

public:
	static Camera* GetInstance();
	static void Release();
	static void Update();

	static void SetPosition(int _x, int _y);
	static void SetTarget(GameObject* _target);
	static void SetRangeX(int minX, int maxX);
	static void SetRangeY(int minY, int maxY);
	static float GetX();
	static float GetY();

	static void FollowTarget();

	D3DXVECTOR3 position;
	D3DXVECTOR3 minPos;
	D3DXVECTOR3 maxPos;
	GameObject* target = nullptr;
};

