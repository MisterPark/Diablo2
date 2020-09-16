#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
	memset(&imageInfo, 0, sizeof(D3DXIMAGE_INFO));
}

Texture::~Texture()
{
}

int Texture::GetSpriteWidth()const
{
	//if (this == nullptr) return 0;
	return imageInfo.Width / colCount;
}

int Texture::GetSpriteHeight()const
{
	if (this == nullptr) return 0;
	return imageInfo.Height / rowCount;
}
