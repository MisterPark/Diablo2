#pragma once
#include <d3dx9.h>

class Vector3 : public D3DXVECTOR3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();


};

typedef D3DXMATRIX Matrix;

//
//class Matrix : public D3DXMATRIX
//{
//public:
//	using D3DXMATRIX::operator const FLOAT*;
//	using D3DXMATRIX::operator FLOAT*;
//	using D3DXMATRIX::operator*;
//	using D3DXMATRIX::operator();
//	using D3DXMATRIX::operator*=;
//	using D3DXMATRIX::operator+;
//	using D3DXMATRIX::operator+=;
//	using D3DXMATRIX::operator-;
//	using D3DXMATRIX::operator-=;
//	using D3DXMATRIX::operator/;
//	using D3DXMATRIX::operator/=;
//	using D3DXMATRIX::operator==;
//	using D3DXMATRIX::operator!=;
//};