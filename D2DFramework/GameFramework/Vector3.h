#pragma once
#include <d3dx9.h>

class Vector3 : public D3DXVECTOR3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();


};

class Matrix : public D3DXMATRIX
{
public:

};