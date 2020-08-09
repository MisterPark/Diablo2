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
	static int GetX();
	static int GetY();

	static void FollowTarget();

	Transform position{ 0.f,0.f };
	Transform minPos{ 0.f,0.f };
	Transform maxPos{ 0.f,0.f };
	GameObject* target = nullptr;
};

