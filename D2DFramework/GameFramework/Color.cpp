#include "pch.h"
#include "Color.h"

Color::Color(D3DXCOLOR r)
{
	this->a = r.a;
	this->r = r.r;
	this->g = r.g;
	this->b = r.b;
}

Color::Color(float a, float r, float g, float b)
{
	this->a = a;
	this->r = r;
	this->g = g;
	this->b = b;

}
