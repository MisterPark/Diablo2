#include "pch.h"
#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(D3DXVECTOR3 r)
{
	this->x = r.x;
	this->y = r.y;
	this->z = r.z;
}

Vector3::Vector3(POINT r)
{
	this->x = r.x;
	this->y = r.y;
	this->z = 0.f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
}
