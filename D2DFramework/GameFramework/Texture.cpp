#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
	memset(&imageInfo, 0, sizeof(D3DXIMAGE_INFO));
}

Texture::~Texture()
{
}

DWORD Texture::GetLastFrame()
{
	return colCount-1;
}
