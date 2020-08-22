#pragma once

#include "Vector3.h"

class Transform
{
public:
	Transform();
	~Transform();

	Vector3 position{ 0.f,0.f,0.f };
	Vector3 rotation{ 0.f,0.f,0.f };
	Vector3 scale{ 1.f,1.f,1.f };
};

